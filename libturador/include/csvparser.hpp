#ifndef LIBTURADOR_CSVPARSER_HPP_INCLUDED
#define LIBTURADOR_CSVPARSER_HPP_INCLUDED

#include <fstream>
#include <limits>
#include <sstream>

class CsvRow
{
public:
  std::stringstream stream;
  char row[1024];
};

class CsvParser
{
private:
  const char* filePath = nullptr;

  std::ifstream fileStream;

public:
  void OpenFile(const char* const filePath)
  {
    if (filePath == nullptr)
    {
      // TODO: Throw.
    }

    fileStream = std::ifstream(filePath);

    // Check if the file really opened.
    if (!fileStream.is_open())
    {
      // TODO: Throw.
    }

    this->filePath = filePath;
  }

  CsvRow ParseNextRow()
  {
    if (filePath == nullptr)
    {
      // TODO: Throw.
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

    // Ignore the \n.
    if (fileStream.peek() != '\n')
    {
      // TODO: Throw.
    }
    // fileStream.ignore();

    return row;
  }

  void ParseNextColumn(CsvRow& row, char* const columnBuffer, const int columnBufferSize) const
  {
    if (columnBuffer == nullptr)
    {
      // TODO: Throw.
    }

    row.stream.getline(columnBuffer, columnBufferSize, ';');
  }

  void IgnoreNextColumn(CsvRow& row) const { row.stream.ignore(std::numeric_limits<int>::max(), ';'); }
};

#endif // LIBTURADOR_CSVPARSER_HPP_INCLUDED
