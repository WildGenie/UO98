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
                PlayerObject player;
                if(Server.TryFindObject(serial, out player))
                {

                    HelpInfoArgs args = new HelpInfoArgs()
                    {
                        mode = 2,
                        gm_serial = GMSerial,
                        player_serial = player.Serial,
                        location = player.Location,
                        account_number = player.AccountNumber,
                        character_number = (byte)player.CharacterNumber,
                    };

                    unsafe
                    {
                        string name = player.MobileObject.RealName;
                        fixed(char* chars = name)
                            ASCIIEncoding.ASCII.GetBytes(chars, name.Length, args.CharacterRealName, name.Length);
                    }
                    Server.SendInfoWindowOrDoPlayerShadow(args);
                }
                else
                    Server.SendSystemMessage(GMSerial, "That object is not a player.");
            }
        }
    }
}
