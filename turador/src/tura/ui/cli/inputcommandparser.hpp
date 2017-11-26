#ifndef TURADOR_TURA_UI_CLI_INPUTCOMMANDPARSER_HPP_INCLUDED
#define TURADOR_TURA_UI_CLI_INPUTCOMMANDPARSER_HPP_INCLUDED

#include <sstream>

#include <tura/helpers/array.hpp>
#include <tura/helpers/chararray.hpp>
#include <tura/helpers/noncopyable.h>

#include "tura/ui/cli/inputcommand.hpp"

namespace tura
{
namespace ui
{
namespace cli
{
class InputCommandParametersParser
{
public:
  virtual void Parse(std::istream& stream, InputCommand& command) const = 0;
};

template<typename... Parameters>
class InputCommandParametersParserImpl : public InputCommandParametersParser
{
  void Parse(std::istream& stream, InputCommand& command) const override
  {
    ParseInputCommandParameters<Parameters...>(stream, command);
  }
};

class InputCommandParser : helpers::Noncopyable
{
private:
  helpers::Array<helpers::CharArray<64>, 32> commandNames;
  helpers::Array<InputCommandParametersParser*, 32> inputCommandParametersParsers;

  unsigned int GetCommandNameIndex(helpers::CharArray<64> commandName) const
  {
    for (unsigned int i = 0; i < commandNames.size(); ++i)
    {
      if (commandName == commandNames[i])
      {
        return i;
      }
    }

    // TODO: Throw.
  }

public:
  ~InputCommandParser()
  {
    for (auto parser : inputCommandParametersParsers)
    {
      delete parser;
    }
  }

  template<typename... Parameters>
  void RegisterCommand(helpers::CharArray<64> commandName)
  {
    commandNames.Add(commandName);
    inputCommandParametersParsers.Add(new InputCommandParametersParserImpl<Parameters...>);
  }

  void Clear()
  {
    for (auto parser : inputCommandParametersParsers)
    {
      delete parser;
    }

    commandNames.Clear();
    inputCommandParametersParsers.Clear();
  }

  void UnregisterCommand(helpers::CharArray<64> commandName)
  {
    for (unsigned int i = 0; i < commandNames.size(); ++i)
    {
      if (commandName == commandNames[i])
      {
        delete inputCommandParametersParsers[i];
        inputCommandParametersParsers.Remove(i);
        commandNames.Remove(i);
      }
    }
  }

  InputCommand ParseCommand(std::istream& stream) const
  {
    InputCommand command;

    // Parse the incoming command to a string stream buffer.
    char lineBuffer[64];
    stream.getline(lineBuffer, sizeof(lineBuffer));

    std::stringstream streamBuffer;
    streamBuffer << lineBuffer;

    // Parse the command.
    streamBuffer.getline(command.command.array, command.command.MaxLength(), ' ');

    if (!IsCommandRegistered(command.command))
    {
      throw std::system_error(std::make_error_code(Error::CommandNotRegistered));
    }

    // Parse the command parameters.
    inputCommandParametersParsers[GetCommandNameIndex(command.command)]->Parse(streamBuffer, command);

    return command;
  }

  bool IsCommandRegistered(const helpers::CharArray<64>& commandName) const
  {
    return commandNames.HasValue(commandName);
  }
};
}
}
}

#endif // TURADOR_TURA_UI_CLI_INPUTCOMMANDPARSER_HPP_INCLUDED
