#include "editor.h"

int read_data(int start_bit, int bits_to_read, int& current_byte, FileDescriptorNew* pDescriptorNew)
{
	int shift;
	int pow_of_two[] = {1,2,4,8,16,32,64,128};

	int bytes_advanced = 0;
	int output = 0;
	int bit = start_bit;
	for(int ii=0; ii<bits_to_read; ii++)
	{
		if(bit == 8)
		{
			bit = 0;
			current_byte++;
		}
		if(ii%8 == 0 && ii>0) bytes_advanced++;
		shift = bit-(ii%8);
		if(shift>=0)
			output += ((pDescriptorNew->data[current_byte] >> shift) & pow_of_two[ii % 8]) << bytes_advanced*8;
		else
			output += ((pDescriptorNew->data[current_byte] << -shift) & pow_of_two[ii % 8]) << bytes_advanced*8;
		bit++;
	}
	if(bit == 8) current_byte++;

	return output;
}


void write_data(int input, int start_bit, int bits_to_write, int& current_byte, FileDescriptorNew* pDescriptorNew)
{
	int shift;
	uint8_t pow_of_two[] = {1,2,4,8,16,32,64,128};

	int bytes_advanced = 0;
	int bit = start_bit;
	uint8_t byte_val = pDescriptorNew->data[current_byte];
	for(int ii=0; ii<bits_to_write; ii++)
	{
		if(bit == 8)
		{
			bit = 0;
			pDescriptorNew->data[current_byte] = byte_val;
			current_byte++;
			byte_val = pDescriptorNew->data[current_byte];
		}
		if(ii%8 == 0 && ii>0) bytes_advanced++;
		shift = (ii%8) - bit;
		if(shift>=0)
			byte_val = (byte_val & ~pow_of_two[bit]) + (((input >> bytes_advanced*8) >> shift) & pow_of_two[bit]);
		else
			byte_val = (byte_val & ~pow_of_two[bit]) + (((input >> bytes_advanced*8) << -shift) & pow_of_two[bit]);
		bit++;
	}
	pDescriptorNew->data[current_byte] = byte_val;
	if(bit == 8)
	{
		current_byte++;
	}
}


int read_dataOld(int start_bit, int bits_to_read, int& current_byte, FileDescriptorOld* pDescriptor)
{
	int shift;
	int pow_of_two[] = { 1,2,4,8,16,32,64,128 };

	int bytes_advanced = 0;
	int output = 0;
	int bit = start_bit;
	for (int ii = 0; ii < bits_to_read; ii++)
	{
		if (bit == 8)
		{
			bit = 0;
			current_byte++;
		}
		if (ii % 8 == 0 && ii > 0) bytes_advanced++;
		shift = bit - (ii % 8);
		if (shift >= 0)
			output += ((pDescriptor->data[current_byte] >> shift) & pow_of_two[ii % 8]) << bytes_advanced * 8;
		else
			output += ((pDescriptor->data[current_byte] << -shift) & pow_of_two[ii % 8]) << bytes_advanced * 8;
		bit++;
	}
	if (bit == 8) current_byte++;

	return output;
}


void write_dataOld(int input, int start_bit, int bits_to_write, int& current_byte, FileDescriptorOld* pDescriptor)
{
	int shift;
	uint8_t pow_of_two[] = { 1,2,4,8,16,32,64,128 };

	int bytes_advanced = 0;
	int bit = start_bit;
	uint8_t byte_val = pDescriptor->data[current_byte];
	for (int ii = 0; ii < bits_to_write; ii++)
	{
		if (bit == 8)
		{
			bit = 0;
			pDescriptor->data[current_byte] = byte_val;
			current_byte++;
			byte_val = pDescriptor->data[current_byte];
		}
		if (ii % 8 == 0 && ii > 0) bytes_advanced++;
		shift = (ii % 8) - bit;
		if (shift >= 0)
			byte_val = (byte_val & ~pow_of_two[bit]) + (((input >> bytes_advanced * 8) >> shift) & pow_of_two[bit]);
		else
			byte_val = (byte_val & ~pow_of_two[bit]) + (((input >> bytes_advanced * 8) << -shift) & pow_of_two[bit]);
		bit++;
	}
	pDescriptor->data[current_byte] = byte_val;
	if (bit == 8)
	{
		current_byte++;
	}
}

