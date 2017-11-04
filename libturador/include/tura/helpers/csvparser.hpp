#ifndef LIBTURADOR_TURA_HELPERS_CSVPARSER_HPP_INCLUDED
#define LIBTURADOR_TURA_HELPERS_CSVPARSER_HPP_INCLUDED

#include <fstream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <system_error>

#include "tura/error.h"

namespace tura
{
namespace helpers
{
class CsvRow
{
public:
  std::stringstream stream;
  char row[1024];
};

class CsvParser
{
private:
  const char* filePath;
  bool fileOpened;

  std::ifstream fileStream;

public:
  CsvParser()
    : filePath(nullptr)
    , fileOpened(false)
  {
  }

  void OpenFile(const char* const filePath)
  {
    if (filePath == nullptr)
    {
      throw std::invalid_argument("Argument 'filePath' may not be null.");
    }

    fileStream = std::ifstream(filePath);

    // Check if the file really opened.
    if (!fileStream.is_open())
    {
      throw std::system_error(std::make_error_code(Error::UnableToOpenFile));
    }

    this->filePath = filePath;
    fileOpened = true;
  }

  CsvRow ParseNextRow()
  {
    if (!fileOpened)
    {
      throw std::system_error(std::make_error_code(Error::NoFileOpened));
    }

    // If the line starts with a '#' it's a comment.
    while (fileStream.peek() == '#')
    {
      fileStream.ignore(std::numeric_limits<int>::max(), '\n');
    }

    // Read the line into a row.
    CsvRow row;
    fileStream.getline(row.row, sizeof(row.row), '\n');
    row.stream = std::stringstream(row.row);

    return row;
  }

  void IgnoreNextRow()
  {
    if (!fileOpened)
    {
      throw std::system_error(std::make_error_code(Error::NoFileOpened));
    }

    // If the line starts with a '#' it's a comment.
    while (fileStream.peek() == '#')
    {
      fileStream.ignore(std::numeric_limits<int>::max(), '\n');
    }

    fileStream.ignore(std::numeric_limits<int>::max(), '\n');
  }

  void ParseNextColumn(CsvRow& row, char* const columnBuffer, const int columnBufferSize) const
  {
    if (columnBuffer == nullptr)
    {
      throw std::invalid_argument("Argument 'columnBuffer' may not be null.");
    }

    row.stream.getline(columnBuffer, columnBufferSize, ';');
  }

  void IgnoreNextColumn(CsvRow& row) const { row.stream.ignore(std::numeric_limits<int>::max(), ';'); }
};
}
}

#endif // LIBTURADOR_TURA_HELPERS_CSVPARSER_HPP_INCLUDED
