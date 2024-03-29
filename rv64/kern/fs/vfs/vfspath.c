#include <defs.h>
#include <string.h>
#include <vfs.h>
#include <inode.h>
#include <iobuf.h>
#include <stat.h>
#include <proc.h>
#include <error.h>
#include <assert.h>


static struct inode *
get_cwd_nolock(void) {
    return current->filesp->pwd;
}

static void
set_cwd_nolock(struct inode *pwd) {
    current->filesp->pwd = pwd;
}


static void
lock_cfs(void) {
    lock_files(current->filesp);
}

static void
unlock_cfs(void) {
    unlock_files(current->filesp);
}


int
vfs_get_curdir(struct inode **dir_store) {
    struct inode *node;
    if ((node = get_cwd_nolock()) != NULL) {
        vop_ref_inc(node);
        *dir_store = node;
        return 0;
    }
    return -E_NOENT;
}


int
vfs_set_curdir(struct inode *dir) {
    int ret = 0;
    lock_cfs();
    struct inode *old_dir;
    if ((old_dir = get_cwd_nolock()) != dir) {
        if (dir != NULL) {
            uint32_t type;
            if ((ret = vop_gettype(dir, &type)) != 0) {
                goto out;
            }
            if (!S_ISDIR(type)) {
                ret = -E_NOTDIR;
                goto out;
            }
            vop_ref_inc(dir);
        }
        set_cwd_nolock(dir);
        if (old_dir != NULL) {
            vop_ref_dec(old_dir);
        }
    }
out:
    unlock_cfs();
    return ret;
}


int
vfs_chdir(char *path) {
    int ret;
    struct inode *node;
    if ((ret = vfs_lookup(path, &node)) == 0) {
        ret = vfs_set_curdir(node);
        vop_ref_dec(node);
    }
    return ret;
}

int
vfs_getcwd(struct iobuf *iob) {
    int ret;
    struct inode *node;
    if ((ret = vfs_get_curdir(&node)) != 0) {
        return ret;
    }
    assert(node->in_fs != NULL);

    const char *devname = vfs_get_devname(node->in_fs);
    if ((ret = iobuf_move(iob, (char *)devname, strlen(devname), 1, NULL)) != 0) {
        goto out;
    }
    char colon = ':';
    if ((ret = iobuf_move(iob, &colon, sizeof(colon), 1, NULL)) != 0) {
        goto out;
    }
    ret = vop_namefile(node, iob);

out:
    vop_ref_dec(node);
    return ret;
}

