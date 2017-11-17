#ifndef TURADOR_TURA_UI_INPUTCOMMANDPARSER_HPP_INCLUDED
#define TURADOR_TURA_UI_INPUTCOMMANDPARSER_HPP_INCLUDED

#include <tura/helpers/array.hpp>
#include <tura/helpers/chararray.hpp>

#include "tura/ui/inputcommand.hpp"

namespace tura
{
namespace ui
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

class InputCommandParser
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
  template<typename... Parameters>
  void RegisterCommand(helpers::CharArray<64> commandName)
  {
    commandNames.Add(commandName);
    inputCommandParametersParsers.Add(new InputCommandParametersParser<Parameters...>);
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

    // Parse the command parameters.
    inputCommandParametersParsers[GetCommandNameIndex(command.command)]->Parse(streamBuffer, command);

    return command;
  }
};
}
}

#endif // TURADOR_TURA_UI_INPUTCOMMANDPARSER_HPP_INCLUDED
