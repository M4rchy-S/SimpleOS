#ifndef TTY_H
#define TTY_H

#include "../vga/vga.h"
#include "../libc/string.h"
#include "../time/RTC.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

static void terminal_clear(void)
{
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setup(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	
	terminal_clear();
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

static void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

static void terminal_putchar(char c) 
{
	//	Special symbols
	if(c == '\n')
	{
		terminal_column = 0;

		if (++terminal_row == VGA_HEIGHT)
		{
			terminal_row = 0;
			terminal_clear();
		}
		
		terminal_writestring("> ");

		return;
	}
	else if (c == '\t')
	{
		terminal_column = terminal_column + 4;
		if(terminal_column > VGA_WIDTH)
		{
			terminal_column = terminal_column % VGA_WIDTH;
			
			if (++terminal_row == VGA_HEIGHT)
			{
				terminal_row = 0;
				terminal_clear();
			}

		}
		return;
	}

	//	Regular character
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);

	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;

		if (++terminal_row == VGA_HEIGHT)
		{
			terminal_row = 0;
			terminal_clear();
		}
	}
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

void terminal_backspace()
{
	if( terminal_column  <= 2)
	{
		return;
	}

	const size_t index = terminal_row * VGA_WIDTH + terminal_column - 1;
	terminal_buffer[index] = vga_entry(' ', terminal_color);
	terminal_column -= 1;

}

#define MAX_BUFFER_LENGTH 100
uint32_t buffer_length = 0;
char input_buffer[MAX_BUFFER_LENGTH];

static void handle_command(char *command)
{
	if(strcmp(command, "time") == 0)
	{
		prints("[+] Your time\n");
		print_time();
	}
	else if(strcmp(command, "help") == 0)
	{
		prints("[?] Available commands:\ntime - get current time\n");
	}
	else
	{
		prints("[-] Unknown command\n");
	}
}


void buffer_add_char(char *ch)
{
	if(buffer_length >= MAX_BUFFER_LENGTH - 1)
		return;

	input_buffer[buffer_length] = ch[0];
	buffer_length += 1;
}

void buffer_rem_char()
{
	if(buffer_length <= 0)
		return;

	buffer_length -= 1;
}	

void buffer_process()
{
	input_buffer[buffer_length] = '\0';

	// prints("Processing buffer: ");
	// prints(input_buffer);
	// prints("\n");

	handle_command(input_buffer);

	buffer_length = 0;
	input_buffer[0] = '\0';
	
}


#endif