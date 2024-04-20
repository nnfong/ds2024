const BLOCK = 1024;

typedef char filechunk[BLOCK];
typedef string filename<BLOCK>;

struct buffer {
    filename name;
    filechunk data;
    int numbytes;
};

program FILETRANSFER_PROG {
    version FILETRANSFER_VERS {
        int FILETRANSFER_PROC(buffer) = 1;
    } = 1; 
} = 0x31230000;
