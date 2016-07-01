
#define FUSE_USE_VERSION 30
#include <fuse/fuse.h>
#include <string>

#include "pmds.hpp"
#include "logging.hpp"

metadata * meta;

static void* pmds_init(struct fuse_conn_info *conn)
{
	FUSE_LOG("Peta Filesystem starting ...");
	// Change directories to place the PetaFS coredump in the repo root
	//chdir(config.repoPath.c_str());
	//priv->init();

	FUSE_LOG("Metadata Service starting ...");
	PMDS::instance().init();

	return meta;
}

static int pmds_getattr(const char *path, struct stat *stbuf)
{
	return PMDS::instance().getattr(path, stbuf);
}

static int pmds_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
						off_t offset, struct fuse_file_info *fi)
{

}

static int pmds_open(const char *path, struct fuse_file_info *fi)
{

}

static int pmds_read(const char *path, char *buf, size_t size, off_t offset,
					struct fuse_file_info *fi)
{

}


static struct fuse_operations pmds_oper;

static void setup_pmds_oper()
{
	memset(&pmds_oper, 0, sizeof(struct fuse_operations));
	pmds_oper.init		= pmds_init;
	pmds_oper.getattr	= pmds_getattr;
	pmds_oper.readdir	= pmds_readdir;
	pmds_oper.open		= pmds_open;
	pmds_oper.read		= pmds_read;
};

int main(int argc, char *argv[])
{
	return fuse_main(argc, argv, &pmds_oper, NULL);
}

