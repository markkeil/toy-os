#include "terminal.h"

#define VGA_BUFFER 0xB8000
#define VGA_COLS 80
#define VGA_ROWS 25
#define DEFAULT_COLOR 0x0F

static unsigned short *vga = (unsigned short *) VGA_BUFFER;
static int cursor_row = 0;
static int cursor_col = 0;

// Helpers

static void vga_write_char(char c, int row, int col) {
    vga[row * VGA_COLS + col] = (DEFAULT_COLOR << 8) | c;
}

static void clear_row(int row) {
    for (int col = 0; col < VGA_COLS; col++) {
        vga_write_char(' ', row, col);
    }
}

static void scroll() {
    // Move every row up one row
    for (int row = 1; row < VGA_ROWS; row++) {
        for (int col = 0; col < VGA_COLS; col++) {
            vga[(row - 1) * VGA_COLS + col] = vga[row * VGA_COLS + col];
        }
    }
    // Empty last row
    clear_row(VGA_ROWS - 1);
    cursor_row = VGA_ROWS - 1;
    cursor_col = 0;
}

static void newline() {
    cursor_col = 0;
    cursor_row++;
    if (cursor_row >= VGA_ROWS) {
        scroll();
    }
}

// Public API

void tinit() {
    cursor_row = 0;
    cursor_col = 0;
    for (int row = 0; row < VGA_ROWS; row++) {
        clear_row(row);
    }
}

void tputchar(char c) {
    if(c == '\n') {
        newline();
        return;
    }

    vga_write_char(c, cursor_row, cursor_col);
    cursor_col++;

    if(cursor_col >= VGA_COLS) {
        newline();
    }
}

void tprint(const char *str) {
    int i = 0;
    while (str[i] != '\0') {
        tputchar(str[i]);
        i++;
    }
}

void tprinthex(unsigned int n) {
    tprint("0x");
    char hex_chars[] = "0123456789ABCDEF";
    int started = 0;
    for (int i = 28; i >= 0; i -= 4) {
        int nibble = (n >> i) & 0xF;
        if (nibble !=0 ) started = 1;
        if (started) tputchar(hex_chars[nibble]);
    }
    if (!started) tputchar('0');
}

void tprintint(int n) {
    if (n < 0) {
        tputchar('-');
        n = -n;
    }
    if(n == 0) {
        tputchar('0');
        return;
    }
    char buf[32];
    int i = 0;
    while (n > 0) {
        buf[i++] = '0' + (n % 10);
        n /= 10;
    }
    // Reverse buf
    for (int j = i - 1; j >= 0; j--) {
        tputchar(buf[j]);
    }
}