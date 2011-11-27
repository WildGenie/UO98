using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Sharpkick.Administration
{
    class InvisibleCommand : InvertableScriptCommand
    {
        public InvisibleCommand(GMCommand.CommandParameters CommandParams) : base(CommandParams) { }
        public override string ActionScriptName { get { return "commandInvisible"; } }
        public override string InverseScriptName { get { return "commandVisible"; } }
    }

    class FreezeCommand : InvertableScriptCommand
    {
        public FreezeCommand(GMCommand.CommandParameters CommandParams) : base(CommandParams) { }
        public override string ActionScriptName { get { return "commandFreeze"; } }
        public override string InverseScriptName { get { return "commandUnFreeze"; } }
    }

    class SquelchCommand : InvertableScriptCommand
    {
        public SquelchCommand(GMCommand.CommandParameters CommandParams) : base(CommandParams) { }
        public override string ActionScriptName { get { return "commandSquelch"; } }
        public override string InverseScriptName { get { return "commandUnSquelch"; } }
    }

    class InvulnerableCommand : InvertableScriptCommand
    {
        public InvulnerableCommand(GMCommand.CommandParameters CommandParams) : base(CommandParams) { }
        public override string ActionScriptName { get { return "commandInvulnerable"; } }
        public override string InverseScriptName { get { return "commandVulnerable"; } }
    }

    /// <summary>
    /// This doesn't currently work.
    /// </summary>
    class TransferCommand : SimpleScriptCommand
    {
        public TransferCommand(GMCommand.CommandParameters CommandParams) : base(CommandParams) { }
        public override string ActionScriptName { get { return "commandTransfer"; } }

        public override void Execute()
        {
            Server.setObjVar(TargetSerial, "transLoc", GetGMLocation());

            Server.SendSystemMessage(GMSerial, "Transfer command not yet implemented. Trouble with setObjVar...");

            base.Execute();
        }

        public Location GetGMLocation()
        {
            return Server.getLocation(GMSerial);
        }
    }

    class SlayCommand : SimpleScriptCommand
    {
        public SlayCommand(GMCommand.CommandParameters CommandParams) : base(CommandParams) { }
        public override string ActionScriptName { get { return "commandSlay"; } }
    }

    class DeleteCommand : SimpleScriptCommand
    {
        public DeleteCommand(GMCommand.CommandParameters CommandParams) : base(CommandParams) { }
        public override string ActionScriptName { get { return "commandDelete"; } }
    }

    class ResurrectCommand : SimpleScriptCommand
    {
        public ResurrectCommand(GMCommand.CommandParameters CommandParams) : base(CommandParams) { }
        public override string ActionScriptName { get { return "commandResurrect"; } }
    }

    class LightningCommand : SimpleScriptCommand
    {
        public LightningCommand(GMCommand.CommandParameters CommandParams) : base(CommandParams) { }
        public override string ActionScriptName { get { return "commandLightning"; } }
    }

    class ZapCommand : SimpleScriptCommand
    {
        public ZapCommand(GMCommand.CommandParameters CommandParams) : base(CommandParams) { }
        public override string ActionScriptName { get { return "commandZap"; } }
    }

    /// <summary>
    /// This doesn't currently work. Look at script file.
    /// </summary>
    class KickCommand : SimpleScriptCommand
    {
        public KickCommand(GMCommand.CommandParameters CommandParams) : base(CommandParams) { }
        public override string ActionScriptName { get { return "commandKick"; } }
    }

    abstract class InvertableScriptCommand : SimpleScriptCommand
    {
        public abstract string InverseScriptName { get; }
        public bool InvertAction { get; protected set; }

        public override void Execute()
        {
            if (SerialIsValid())
                AttachScript(InvertAction ? InverseScriptName : ActionScriptName);
        }

        public InvertableScriptCommand(GMCommand.CommandParameters CommandParams) : base(CommandParams)
        {
        
        }

        protected override bool ArgumentsAreValid(string[] args)
        {
            return (args != null && args.Length == 2 && (args[0] == "0" || args[0] == "1"));
        }

        protected override void ReadParameters(string[] args)
        {
            TargetSerial = ReadAsSerial(args[1]);
            InvertAction = args[0] == "0";
        }

        protected override void ReportInvalidParameters()
        {
            Server.SendSystemMessage(GMSerial, "Invalid command syntax: a boolean integer and valid object serial are the required parameters.");
        }

    }

    abstract class SimpleScriptCommand : GMCommand
    {
        public abstract string ActionScriptName { get; }
        public int TargetSerial { get; protected set; }

        public override void Execute()
        {
            if (ArgumentsAreValid(Arguments))
            {
                ReadParameters(Arguments);
                if (!ParametersAreValid())
                    ReportInvalidParameters();
                else if (SerialIsValid())
                    AttachScript(ActionScriptName);
            }
        }

        protected virtual bool SerialIsValid()
        {
            return TargetSerial > 0;
        }

        protected virtual void AttachScript(string ScriptName)
        {
            Server.addScript(TargetSerial, ScriptName);
        }

        public SimpleScriptCommand(GMCommand.CommandParameters CommandParams) : base(CommandParams)
        {
        }

        protected virtual bool ArgumentsAreValid(string[] args)
        {
            return (args != null && args.Length == 1);
        }

        protected virtual bool ParametersAreValid()
        {
            return TargetSerial > 0;
        }

        protected virtual void ReadParameters(string[] args)
        {
            TargetSerial = ReadAsSerial(args[0]);
        }

        public int ReadAsSerial(string text)
        {
            int serial = 0;
            int.TryParse(text, out serial);
            return serial;
        }

        protected virtual void ReportInvalidParameters()
        {
             Server.SendSystemMessage(GMSerial, "Invalid command syntax: a single valid object serial is the required parameter.");
        }
    }

    class InvalidCommand : GMCommand
    {
        public InvalidCommand(GMCommand.CommandParameters CommandParams) : base(CommandParams) { }

        public override void Execute()
        {
            if (string.IsNullOrEmpty(Command))
                Server.SendSystemMessage(GMSerial, "Invalid command syntax: Missing command text.");
            else
                Server.SendSystemMessage(GMSerial, string.Format("GM Command {0} is not implemented.", Command));
        }
    }

    abstract class GMCommand
    {
        public struct CommandParameters
        {
            public int GmSerial;
            public string Command;
            public string[] Arguments;
        }

       public static GMCommand Instantiate(int gmSerial, string command)
        {
            GMCommandFactory factory = new GMCommandFactory(command);
            return factory.ConstructCommandInstance(gmSerial);
        }

        public abstract void Execute();

        public int GMSerial { get; private set; }
        public string Command { get; private set; }
        public string[] Arguments { get; private set; }

        protected GMCommand(GMCommand.CommandParameters CommandParams)
        {
            GMSerial = CommandParams.GmSerial;
            Command = CommandParams.Command;
            Arguments = CommandParams.Arguments;
        }

        private class GMCommandFactory
        {
            private static char[] CommandDelimiterCharacters = new char[] { ' ', '\t' };
            private string[] commandArray;

            public GMCommandFactory(string command)
            {
                commandArray = command.Split(CommandDelimiterCharacters, StringSplitOptions.RemoveEmptyEntries);
            }

            public GMCommand ConstructCommandInstance(int gmSerial)
            {
                CommandParameters CommandParams = new CommandParameters();
                CommandParams.GmSerial = gmSerial;
                CommandParams.Command = Command;
                CommandParams.Arguments = Arguments;

                switch (Command)
                {
                    case "invisible":
                        return new InvisibleCommand(CommandParams);
                    case "freeze":
                        return new FreezeCommand(CommandParams);
                    case "squelch":
                        return new SquelchCommand(CommandParams);
                    case "invulnerable":
                        return new InvulnerableCommand(CommandParams);
                    case "slay":
                        return new SlayCommand(CommandParams);
                    case "transfer":
                        return new TransferCommand(CommandParams);
                    case "delete":
                        return new DeleteCommand(CommandParams);
                    case "resurrect":
                        return new ResurrectCommand(CommandParams);
                    case "lightning":
                        return new LightningCommand(CommandParams);
                    case "zap":
                        return new ZapCommand(CommandParams);
                    case "kick":
                        return new KickCommand(CommandParams);
                    default:
                        return new InvalidCommand(CommandParams);
                }
            }

            public string Command
            {
                get
                {
                    if (commandArray.Length > 0)
                        return commandArray[0];
                    else
                        return string.Empty;
                }
            }

            public string[] Arguments
            {
                get
                {
                    if (commandArray.Length > 1)
                        return commandArray.Skip(1).ToArray();
                    else
                        return null;
                }
            }
        }
    
    }
}
