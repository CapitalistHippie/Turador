#ifndef TURADOR_TURA_UI_CLI_STATEHANDLERS_STATEHANDLER_HPP_INCLUDED
#define TURADOR_TURA_UI_CLI_STATEHANDLERS_STATEHANDLER_HPP_INCLUDED

namespace tura
{
namespace ui
{
namespace cli
{
namespace statehandlers
{
class StateHandler
{
public:
  virtual ~StateHandler() = default;

  virtual void EnterState() = 0;
  virtual void ExitState() noexcept = 0;
  virtual void RenderConsole() const = 0;
};
}
}
}
}

#endif // TURADOR_TURA_UI_CLI_STATEHANDLERS_STATEHANDLER_HPP_INCLUDED
