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
private:
  std::stringstream stream;

public:
  CsvRow(const char* const row)
    : stream(row)
  {
  }

  void ParseNextColumn(char* const columnBuffer, const int columnBufferSize)
  {
    if (columnBuffer == nullptr)
    {
      throw std::invalid_argument("Argument 'columnBuffer' may not be null.");
    }

    stream.getline(columnBuffer, columnBufferSize, ';');
  }

  void IgnoreNextColumn() { stream.ignore(std::numeric_limits<int>::max(), ';'); }

  template<typename T>
  CsvRow& operator>>(T& val)
  {
    char buffer[64];
    ParseNextColumn(buffer, sizeof(buffer));

    auto bufferStream = std::stringstream(buffer);

    bufferStream >> val;

    return *this;
  }
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
    char buffer[1024];
    fileStream.getline(buffer, sizeof(buffer), '\n');

    return CsvRow(buffer);
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
};
}
}

#endif // LIBTURADOR_TURA_HELPERS_CSVPARSER_HPP_INCLUDED
