#include <defs.h>
#include <stdio.h>
#include <string.h>
#include <atomic.h>
#include <vfs.h>
#include <inode.h>
#include <error.h>
#include <assert.h>
#include <kmalloc.h>


struct inode *
__alloc_inode(int type) {
    struct inode *node;
    if ((node = kmalloc(sizeof(struct inode))) != NULL) {
        node->in_type = type;
    }
    return node;
}


void
inode_init(struct inode *node, const struct inode_ops *ops, struct fs *fs) {
    node->ref_count = 0;
    node->open_count = 0;
    node->in_ops = ops, node->in_fs = fs;
    vop_ref_inc(node);
}


void
inode_kill(struct inode *node) {
    assert(inode_ref_count(node) == 0);
    assert(inode_open_count(node) == 0);
    kfree(node);
}


int
inode_ref_inc(struct inode *node) {
    node->ref_count += 1;
    return node->ref_count;
}


int
inode_ref_dec(struct inode *node) {
    assert(inode_ref_count(node) > 0);
    int ref_count, ret;
    node->ref_count-= 1;
    ref_count = node->ref_count;
    if (ref_count == 0) {
        if ((ret = vop_reclaim(node)) != 0 && ret != -E_BUSY) {
            cprintf("vfs: warning: vop_reclaim: %e.\n", ret);
        }
    }
    return ref_count;
}


int
inode_open_inc(struct inode *node) {
    node->open_count += 1;
    return node->open_count;
}


int
inode_open_dec(struct inode *node) {
    assert(inode_open_count(node) > 0);
    int open_count, ret;
    node->open_count -= 1;
    open_count = node->open_count;
    if (open_count == 0) {
        if ((ret = vop_close(node)) != 0) {
            cprintf("vfs: warning: vop_close: %e.\n", ret);
        }
    }
    return open_count;
}


void
inode_check(struct inode *node, const char *opstr) {
    assert(node != NULL && node->in_ops != NULL);
    assert(node->in_ops->vop_magic == VOP_MAGIC);
    int ref_count = inode_ref_count(node), open_count = inode_open_count(node);
    assert(ref_count >= open_count && open_count >= 0);
    assert(ref_count < MAX_INODE_COUNT && open_count < MAX_INODE_COUNT);
}

