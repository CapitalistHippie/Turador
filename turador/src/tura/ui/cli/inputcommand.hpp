#ifndef TURADOR_TURA_UI_CLI_INPUTCOMMAND_HPP_INCLUDED
#define TURADOR_TURA_UI_CLI_INPUTCOMMAND_HPP_INCLUDED

#include <system_error>

#include <tura/error.h>
#include <tura/helpers/array.hpp>
#include <tura/helpers/chararray.hpp>

namespace tura
{
namespace ui
{
namespace cli
{
class InputCommandParameter
{
public:
  virtual ~InputCommandParameter() = default;
  virtual void* Get() noexcept = 0;
  virtual InputCommandParameter* Clone() const noexcept = 0;
};

template<typename ParameterType>
class InputCommandParameterImpl : public InputCommandParameter
{
private:
  ParameterType parameter;

public:
  InputCommandParameterImpl(const ParameterType& parameter)
    : parameter(parameter)
  {
  }

  void* Get() noexcept override { return &parameter; }

  InputCommandParameter* Clone() const noexcept override { return new InputCommandParameterImpl(*this); }
};

class InputCommand
{
private:
  helpers::Array<InputCommandParameter*, 32> parameters;

public:
  helpers::CharArray<64> command;

  InputCommand() = default;

  ~InputCommand() noexcept
  {
    for (auto* const parameter : parameters)
    {
      delete parameter;
    }
  }

  InputCommand(const InputCommand& other)
    : command(other.command)
  {
    for (const auto* const parameter : other.parameters)
    {
      parameters.Add(parameter->Clone());
    }
  }

  InputCommand& operator=(const InputCommand& other)
  {
    command = other.command;

    for (const auto* const parameter : other.parameters)
    {
      parameters.Add(parameter->Clone());
    }

    return *this;
  }

  InputCommand(InputCommand&& other)
    : parameters(other.parameters)
    , command(other.command)
  {
    other.parameters.Clear();
  }

  InputCommand& operator=(InputCommand&& other)
  {
    parameters = other.parameters;
    command = other.command;

    other.parameters.Clear();
  }

  unsigned int GetAmountOfParameters() const noexcept { return parameters.size(); }

  template<typename ParameterType>
  void AddParameter(ParameterType parameter)
  {
    parameters.Add(new InputCommandParameterImpl<ParameterType>(parameter));
  }

  template<typename T>
  T& GetParameter(unsigned int index) const
  {
    return *static_cast<T*>(parameters[index]->Get());
  }
}; // class InputCommand

template<typename... Parameters>
struct ParseInputCommandParametersImpl;

template<typename Parameter, typename... Parameters>
struct ParseInputCommandParametersImpl<Parameter, Parameters...>
{
  static void Parse(std::istream& stream, InputCommand& command)
  {
    Parameter parameter;

    stream >> parameter;
    if (stream.fail())
    {
      throw std::system_error(std::make_error_code(Error::InvalidOutputType));
    }

    command.AddParameter(parameter);

    ParseInputCommandParametersImpl<Parameters...>::Parse(stream, command);
  }
};

template<typename... Parameters>
struct ParseInputCommandParametersImpl<helpers::CharArray<64>, Parameters...>
{
  static void Parse(std::istream& stream, InputCommand& command)
  {
    helpers::CharArray<64> arrayParameter;

    stream.getline(arrayParameter.array, arrayParameter.MaxLength(), ' ');
    if (stream.fail())
    {
      throw std::system_error(std::make_error_code(Error::InvalidOutputType));
    }

    command.AddParameter(arrayParameter);

    ParseInputCommandParametersImpl<Parameters...>::Parse(stream, command);
  }
};

template<>
struct ParseInputCommandParametersImpl<helpers::CharArray<64>>
{
  static void Parse(std::istream& stream, InputCommand& command)
  {
    helpers::CharArray<64> arrayParameter;

    stream.getline(arrayParameter.array, arrayParameter.MaxLength());
    if (stream.fail())
    {
      throw std::system_error(std::make_error_code(Error::InvalidOutputType));
    }

    command.AddParameter(arrayParameter);
  }
};

template<>
struct ParseInputCommandParametersImpl<>
{
  static void Parse(std::istream& stream, InputCommand& command) {}
};

template<typename... Parameters>
void ParseInputCommandParameters(std::istream& stream, InputCommand& command)
{
  ParseInputCommandParametersImpl<Parameters...>::Parse(stream, command);
}

template<typename... Parameters>
InputCommand ParseInputCommand(std::istream& stream)
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
  ParseInputCommandParameters<Parameters...>(streamBuffer, command);

  return command;
}
} // namespace cli
} // namespace ui
} // namespace tura

#endif // #ifndef TURADOR_TURA_UI_CLI_INPUTCOMMAND_HPP_INCLUDED
