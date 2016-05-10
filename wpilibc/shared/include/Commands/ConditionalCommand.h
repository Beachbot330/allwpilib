/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2017. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include "Commands/Command.h"

namespace frc {

/**
 * A {@link ConditionalCommand} is a {@link Command} that starts one of two
 * commands.
 *
 * <p>
 * A {@link ConditionalCommand} uses {@link ConditionalCommand#Condition} to
 * determine whether it should run
 * {@link ConditionalCommand#m_onTrue} or {@link ConditionalCommand#m_onFalse}.
 * </p>
 *
 * <p>
 * A {@link ConditionalCommand} adds the proper {@link Command} to the {@link
 * Scheduler} during {@link ConditionalCommand#Initialize()}
 * and then {@link ConditionalCommand#IsFinished()} will return true once that
 * {@link Command} has finished executing.
 * </p>
 *
 * @see Command
 * @see Scheduler
 */
class ConditionalCommand : public Command {
 public:
  ConditionalCommand(Command* onTrue, Command* onFalse);
  ConditionalCommand(const std::string& name, Command* onTrue,
                     Command* onFalse);
  virtual ~ConditionalCommand() = default;

 protected:
  /**
   * The Condition to test to determine which Command to run.
   *
   * @return true if m_onTrue should be run or false if m_onFalse should be run.
   */
  virtual bool Condition() = 0;

  void _Initialize() override;
  void _Cancel() override;
  bool IsFinished() override;
  void Interrupted() override;

 private:
  /**
   * The Command to execute if {@link ConditionalCommand#Condition()} returns
   * true
   */
  Command* m_onTrue;

  /**
   * The Command to execute if {@link ConditionalCommand#Condition()} returns
   * false
   */
  Command* m_onFalse;

  /**
   * Stores command chosen by condition
   */
  Command* m_chosenCommand = nullptr;
};

}  // namespace frc
