#ifndef __KERN_FS_VFS_VFS_H__
#define __KERN_FS_VFS_VFS_H__

#include <defs.h>
#include <fs.h>
#include <sfs.h>

struct inode;   // abstract structure for an on-disk file (inode.h)
struct device;  // abstract structure for a device (dev.h)
struct iobuf;   // kernel or userspace I/O buffer (iobuf.h)


struct fs {
    union {
        struct sfs_fs __sfs_info;                   
    } fs_info;                                     // filesystem-specific data 
    enum {
        fs_type_sfs_info,
    } fs_type;                                     // filesystem type 
    int (*fs_sync)(struct fs *fs);                 // Flush all dirty buffers to disk 
    struct inode *(*fs_get_root)(struct fs *fs);   // Return root inode of filesystem.
    int (*fs_unmount)(struct fs *fs);              // Attempt unmount of filesystem.
    void (*fs_cleanup)(struct fs *fs);             // Cleanup of filesystem.???
};

#define __fs_type(type)                                             fs_type_##type##_info

#define check_fs_type(fs, type)                                     ((fs)->fs_type == __fs_type(type))

#define __fsop_info(_fs, type) ({                                   \
            struct fs *__fs = (_fs);                                \
            assert(__fs != NULL && check_fs_type(__fs, type));      \
            &(__fs->fs_info.__##type##_info);                       \
        })

#define fsop_info(fs, type)                 __fsop_info(fs, type)

#define info2fs(info, type)                                         \
    to_struct((info), struct fs, fs_info.__##type##_info)

struct fs *__alloc_fs(int type);

#define alloc_fs(type)                                              __alloc_fs(__fs_type(type))

// Macros to shorten the calling sequences.
#define fsop_sync(fs)                       ((fs)->fs_sync(fs))
#define fsop_get_root(fs)                   ((fs)->fs_get_root(fs))
#define fsop_unmount(fs)                    ((fs)->fs_unmount(fs))
#define fsop_cleanup(fs)                    ((fs)->fs_cleanup(fs))


void vfs_init(void);
void vfs_cleanup(void);
void vfs_devlist_init(void);


int vfs_set_curdir(struct inode *dir);
int vfs_get_curdir(struct inode **dir_store);
int vfs_get_root(const char *devname, struct inode **root_store);
const char *vfs_get_devname(struct fs *fs);



int vfs_open(char *path, uint32_t open_flags, struct inode **inode_store);
int vfs_close(struct inode *node);
int vfs_link(char *old_path, char *new_path);
int vfs_symlink(char *old_path, char *new_path);
int vfs_readlink(char *path, struct iobuf *iob);
int vfs_mkdir(char *path);
int vfs_unlink(char *path);
int vfs_rename(char *old_path, char *new_path);
int vfs_chdir(char *path);
int vfs_getcwd(struct iobuf *iob);



int vfs_lookup(char *path, struct inode **node_store);
int vfs_lookup_parent(char *path, struct inode **node_store, char **endp);


int vfs_set_bootfs(char *fsname);
int vfs_get_bootfs(struct inode **node_store);

int vfs_add_fs(const char *devname, struct fs *fs);
int vfs_add_dev(const char *devname, struct inode *devnode, bool mountable);

int vfs_mount(const char *devname, int (*mountfunc)(struct device *dev, struct fs **fs_store));
int vfs_unmount(const char *devname);
int vfs_unmount_all(void);

#endif 

