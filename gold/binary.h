// binary.h -- binary input files for gold   -*- C++ -*-

// Copyright 2008 Free Software Foundation, Inc.
// Written by Ian Lance Taylor <iant@google.com>.

// This file is part of gold.

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
// MA 02110-1301, USA.

// Support binary input files by making them look like an CGC file.

#ifndef GOLD_BINARY_H
#define GOLD_BINARY_H

#include <string>

#include "cgccpp.h"

namespace gold
{

class Task;

template<typename Stringpool_char>
class Stringpool_template;

// This class takes a file name and creates a buffer which looks like
// an CGC file read into memory.

class Binary_to_cgc
{
 public:
  Binary_to_cgc(cgccpp::EM machine, int size, bool big_endian,
		const std::string& filename);

  ~Binary_to_cgc();

  // Read contents and create an CGC buffer.  Return true if this
  // succeeds, false otherwise.
  bool
  convert(const Task*);

  // Return a pointer to the contents of the CGC file.
  const unsigned char*
  converted_data() const
  { return this->data_; }

  // Return a pointer to the contents of the CGC file and let the
  // caller take charge of it.  It was allocated using new[].
  unsigned char*
  converted_data_leak()
  {
    unsigned char* ret = this->data_;
    this->data_ = NULL;
    return ret;
  }

  // Return the size of the CGC file.
  size_t
  converted_size() const
  { return this->filesize_; }

 private:
  Binary_to_cgc(const Binary_to_cgc&);
  Binary_to_cgc& operator=(const Binary_to_cgc&);

  template<int size, bool big_endian>
  bool
  sized_convert(const Task*);

  template<int size, bool big_endian>
  void
  write_file_header(unsigned char**);

  template<int size, bool big_endian>
  void
  write_section_header(const char*, const Stringpool_template<char>*,
		       cgccpp::SHT, unsigned int, section_size_type,
		       section_size_type, unsigned int, unsigned int,
		       unsigned int, unsigned int, unsigned char**);

  template<int size, bool big_endian>
  void
  write_symbol(const std::string&, const Stringpool_template<char>*,
	       section_size_type, unsigned int, unsigned char**);

  // The CGC machine code of the file to create.
  cgccpp::EM cgc_machine_;
  // The size of the file to create, 32 or 64.
  int size_;
  // Whether to create a big endian file.
  bool big_endian_;
  // The name of the file to read.
  std::string filename_;
  // The CGC file data, allocated by new [].
  unsigned char* data_;
  // The CGC file size.
  section_size_type filesize_;
};

} // End namespace gold.

#endif // !defined(GOLD_BINARY_H)
