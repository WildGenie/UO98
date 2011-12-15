using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Sharpkick.Administration
{
    class PlayerInfoCommand : GMCommand
    {
        public PlayerInfoCommand(GMCommand.CommandParameters CommandParams) : base(CommandParams) { }

        public override void Execute()
        {
            int serial;
            if(Arguments.Length != 1 || !int.TryParse(Arguments[0], out serial))
            {
                Server.SendSystemMessage(GMSerial, "Invalid command syntax, usage: info <serial>");
            }
            else
            {
                HelpInfoArgs args = new HelpInfoArgs()
                {
                    mode=2,
                    gm_serial = GMSerial,
                    player_serial=serial,
                    location=new Location(1,2,3),
                    account_number = 42,
                    character_number=3,
                };

                unsafe
                {
                    string name="hello there";
                    fixed(char* chars = name)
                        ASCIIEncoding.ASCII.GetBytes(chars, name.Length, args.CharacterRealName, name.Length);
                }
                Server.SendInfoWindowOrDoPlayerShadow(args);
            }
        }
    }
}
