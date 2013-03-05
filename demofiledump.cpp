//====== Copyright (c) 2012, Valve Corporation, All rights reserved. ========//
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
//
// Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
// Redistributions in binary form must reproduce the above copyright notice, 
// this list of conditions and the following disclaimer in the documentation 
// and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
// THE POSSIBILITY OF SUCH DAMAGE.
//===========================================================================//

#include <stdarg.h>
#include <conio.h>
#include "demofile.h"
#include "demofiledump.h"

#include "protobuf-2.4.1/src/google/protobuf/descriptor.h"
#include "protobuf-2.4.1/src/google/protobuf/reflection_ops.h"
#include "protobuf-2.4.1/src/google/protobuf/descriptor.pb.h"

#include "generated_proto/usermessages.pb.h"
#include "generated_proto/ai_activity.pb.h"
#include "generated_proto/dota_modifiers.pb.h"
#include "generated_proto/dota_commonmessages.pb.h"
#include "generated_proto/dota_usermessages.pb.h"

#include "classes.h"

DotaClassContainer dotaClassContainer;

unsigned int entities[427] = {0, 1, 2, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 165, 166, 169, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 279, 350, 351, 352, 353, 355, 742, 743, 744, 745, 746, 747, 748, 749, 750, 751, 752, 753, 754, 755, 756, 757, 758, 759, 760, 767, 768, 775, 776, 777, 778, 779, 780, 781, 785, 820, 821, 822, 823, 824, 825, 826, 910, 912, 918, 919, 920, 921, 922, 923, 1117, 1118, 1119, 1120, 1121, 1122, 1123, 1124, 1125, 1126, 1127, 1128, 1129, 1130, 1131, 1132, 1133, 1134, 1135, 1136, 1137, 1138, 1139, 1140, 1141, 1142, 1143, 1144, 1145, 1146, 1147, 1148, 1149, 1150, 1151, 1152, 1153, 1154, 1155, 1156, 1157, 1158, 1159, 1160, 1161, 1162, 1163, 1164, 1165, 1166, 1167, 1168, 1169, 1170, 1171, 1172, 1173, 1174, 1175, 1176, 1177, 1178, 1179, 1180, 1182, 1183, 1184, 1185, 1186, 1187, 1188, 1189, 1190, 1191, 1192, 1193, 1194, 1195, 1196, 1197, 1198, 1381, 1382, 1383, 1384, 1385, 1386, 1387, 1388, 1389, 1390, 1391, 1392, 1393, 1394, 1395, 1396, 1397, 1398, 1399, 1400, 1401, 1402, 1403, 1404, 1405, 1406, 1407, 1408, 1409, 1410, 1411, 1412, 1413, 1414, 1415, 1416, 1417, 1418, 1419, 1420, 1421, 1422, 1423, 1424, 1425, 1426, 1427, 1428, 1429, 1430, 1431, 1432, 1433, 1434, 1435, 1436, 1437, 1438, 1439, 1440, 1441, 1442, 1443, 1444, 1445, 1446, 1447, 1448, 1449, 1450, 1451, 1452, 1453, 1454, 1455, 1456, 1457, 1458, 1459, 1460, 1461, 1462, 1463, 1464, 1465, 1466, 1467, 1468, 1469, 1470, 1471, 1472, 1475, 1476, 1477, 1478, 1479, 1480, 1481, 1482, 1483, 1484, 1485, 1486, 1487, 1488, 1489, 1490, 1491, 1492, 1493, 1494, 1495, 1496, 1497, 1498, 1499, 1500, 1501, 1502, 1503, 1504, 1505, 1506, 1507, 1508, 1509, 1510, 1511, 1512};

unsigned int classID[427] = {552,409,409,413,413,413,413,278,408,282,282,282,283,283,283,407,412,406,406,405,405,8,403,231,231,403,403,403,403,403,403,403,403,
	403,410,410,410,403,403,403,403,403,403,403,403,410,410,410,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,
	403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,8,231,227,410,425,425,425,
	425,425,425,425,8,8,8,8,8,425,425,425,8,425,425,425,425,425,425,425,8,425,8,425,425,425,425,425,425,425,425,425,
	425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,
	425,425,425,425,425,417,8,8,8,8,8,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
	16,16,16,16,16,16,231,231,410,410,410,410,410,410,410,231,227,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,551,438,476,433,8,8,8,8,8,8,8,8,8,
	8,8,8,8,279,1,1,425,8,8,8,8,8,8,8,8,8,8,404,232,217,217,218,218,218,218,232,218,217,232,217,218,
	218,218,232,218,218,218,218,218,218,217,217,232,232,232,232,232,232,232,218,226,290,417,237,218,217,217,218,218,218,218,218,217,
	217,232,218,218,232,232,218,218,218,218,218,217,217,232,232,232,232,232,232,232,218,218,232,290,226,417,417,460,460,460,460,460,
	460,417,417,417,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8};

__declspec( noreturn ) void fatal_errorf( const char* fmt, ... )
{
    va_list  vlist;
    char buf[ 1024 ];

    va_start( vlist, fmt);
    vsnprintf( buf, sizeof( buf ), fmt, vlist );
	buf[ sizeof( buf ) - 1 ] = 0;
    va_end( vlist );

    fprintf( stderr, "\nERROR: %s\n", buf );
    exit( -1 );
}

bool CDemoFileDump::Open( const char *filename )
{
	if ( !m_demofile.Open( filename ) )
	{
		fprintf( stderr, "Couldn't open '%s'\n", filename );
		return false;
	}

	return true;
}

void CDemoFileDump::MsgPrintf( const ::google::protobuf::Message& msg, int size, const char *fmt, ... )
{
	va_list vlist;
	const std::string& TypeName = msg.GetTypeName();

	// Print the message type and size
	printf( "---- %s (%d bytes) -----------------\n", TypeName.c_str(), size );

	va_start( vlist, fmt);
	vprintf( fmt, vlist );
	va_end( vlist );
}

template < class T, int msgType >
void PrintUserMessage( CDemoFileDump& Demo, const void *parseBuffer, int BufferSize )
{
	T msg;

	if( msg.ParseFromArray( parseBuffer, BufferSize ) )
	{
		Demo.MsgPrintf( msg, BufferSize, "%s", msg.DebugString().c_str() );
	}
}

void CDemoFileDump::DumpUserMessage( const void *parseBuffer, int BufferSize )
{
	CSVCMsg_UserMessage userMessage;

	if( userMessage.ParseFromArray( parseBuffer, BufferSize ) )
	{
		int Cmd = userMessage.msg_type();
		int SizeUM = userMessage.msg_data().size();
		const void *parseBufferUM = &userMessage.msg_data()[ 0 ];

		switch( Cmd )
		{
#define HANDLE_UserMsg( _x )			case UM_ ## _x: PrintUserMessage< CUserMsg_ ## _x, UM_ ## _x >( *this, parseBufferUM, SizeUM ); break
#define HANDLE_DOTA_UserMsg( _x )		case DOTA_UM_ ## _x: PrintUserMessage< CDOTAUserMsg_ ## _x, DOTA_UM_ ## _x >( *this, parseBufferUM, SizeUM ); break

		default:
			printf( "WARNING. DumpUserMessage(): Unknown user message %d.\n", Cmd );
			break;

		HANDLE_UserMsg( AchievementEvent );            	// 1,
		HANDLE_UserMsg( CloseCaption );                 // 2,
		//$ HANDLE_UserMsg( CloseCaptionDirect );       // 3,
		HANDLE_UserMsg( CurrentTimescale );             // 4,
		HANDLE_UserMsg( DesiredTimescale );             // 5,
		HANDLE_UserMsg( Fade );                         // 6,
		HANDLE_UserMsg( GameTitle );                    // 7,
		HANDLE_UserMsg( Geiger );                       // 8,
		HANDLE_UserMsg( HintText );                     // 9,
		HANDLE_UserMsg( HudMsg );                       // 10,
		HANDLE_UserMsg( HudText );                      // 11,
		HANDLE_UserMsg( KeyHintText );                  // 12,
		HANDLE_UserMsg( MessageText );                  // 13,
		HANDLE_UserMsg( RequestState );                 // 14,
		HANDLE_UserMsg( ResetHUD );                     // 15,
		HANDLE_UserMsg( Rumble );                       // 16,
		HANDLE_UserMsg( SayText );                      // 17,
		HANDLE_UserMsg( SayText2 );                     // 18,
		HANDLE_UserMsg( SayTextChannel );               // 19,
		HANDLE_UserMsg( Shake );                        // 20,
		HANDLE_UserMsg( ShakeDir );                     // 21,
		HANDLE_UserMsg( StatsCrawlMsg );                // 22,
		HANDLE_UserMsg( StatsSkipState );               // 23,
		HANDLE_UserMsg( TextMsg );                      // 24,
		HANDLE_UserMsg( Tilt );                         // 25,
		HANDLE_UserMsg( Train );                        // 26,
		HANDLE_UserMsg( VGUIMenu );                     // 27,
		HANDLE_UserMsg( VoiceMask );                    // 28,
		HANDLE_UserMsg( VoiceSubtitle );                // 29,
		HANDLE_UserMsg( SendAudio );                    // 30,

		//$ HANDLE_DOTA_UserMsg( AddUnitToSelection );  // 64,
		HANDLE_DOTA_UserMsg( AIDebugLine );             // 65,
		HANDLE_DOTA_UserMsg( ChatEvent );               // 66,
		HANDLE_DOTA_UserMsg( CombatHeroPositions );     // 67,
		HANDLE_DOTA_UserMsg( CombatLogData );           // 68,
		//$ HANDLE_DOTA_UserMsg( CombatLogName );       // 69,
		HANDLE_DOTA_UserMsg( CombatLogShowDeath );      // 70,
		HANDLE_DOTA_UserMsg( CreateLinearProjectile );  // 71,
		HANDLE_DOTA_UserMsg( DestroyLinearProjectile ); // 72,
		HANDLE_DOTA_UserMsg( DodgeTrackingProjectiles );// 73,
		HANDLE_DOTA_UserMsg( GlobalLightColor );        // 74,
		HANDLE_DOTA_UserMsg( GlobalLightDirection );    // 75,
		HANDLE_DOTA_UserMsg( InvalidCommand );          // 76,
		HANDLE_DOTA_UserMsg( LocationPing );            // 77,
		HANDLE_DOTA_UserMsg( MapLine );                 // 78,
		HANDLE_DOTA_UserMsg( MiniKillCamInfo );         // 79,
		HANDLE_DOTA_UserMsg( MinimapDebugPoint );       // 80,
		HANDLE_DOTA_UserMsg( MinimapEvent );            // 81,
		HANDLE_DOTA_UserMsg( NevermoreRequiem );        // 82,
		HANDLE_DOTA_UserMsg( OverheadEvent );           // 83,
		HANDLE_DOTA_UserMsg( SetNextAutobuyItem );      // 84,
		HANDLE_DOTA_UserMsg( SharedCooldown );          // 85,
		HANDLE_DOTA_UserMsg( SpectatorPlayerClick );    // 86,
		HANDLE_DOTA_UserMsg( TutorialTipInfo );         // 87,
		HANDLE_DOTA_UserMsg( UnitEvent );               // 88,
		HANDLE_DOTA_UserMsg( ParticleManager );         // 89,
		HANDLE_DOTA_UserMsg( BotChat );                 // 90,
		HANDLE_DOTA_UserMsg( HudError );                // 91,
		HANDLE_DOTA_UserMsg( ItemPurchased );           // 92,
		HANDLE_DOTA_UserMsg( Ping );                    // 93

#undef HANDLE_UserMsg
#undef HANDLE_DOTA_UserMsg
		}
	}
}

template < class T, int msgType >
void PrintNetMessage( CDemoFileDump& Demo, const void *parseBuffer, int BufferSize )
{
	T msg;

	/*if( msg.ParseFromArray( parseBuffer, BufferSize ) )
	{
		if( msgType == svc_GameEventList )
		{
			Demo.m_GameEventList.CopyFrom( msg );
		}

		Demo.MsgPrintf( msg, BufferSize, "%s", msg.DebugString().c_str() );
	}*/
}

template <>
void PrintNetMessage<CSVCMsg_SendTable, svc_SendTable>( CDemoFileDump& Demo, const void *parseBuffer, int BufferSize )
{
	CSVCMsg_SendTable msg;

	if( msg.ParseFromArray( parseBuffer, BufferSize ) )
	{
		Demo.MsgPrintf( msg, BufferSize, "%s", msg.DebugString().c_str() );
	}
}

template <>
void PrintNetMessage< CSVCMsg_UserMessage, svc_UserMessage >( CDemoFileDump& Demo, const void *parseBuffer, int BufferSize )
{
	Demo.DumpUserMessage( parseBuffer, BufferSize );
}

template <>
void PrintNetMessage< CSVCMsg_GameEvent, svc_GameEvent >( CDemoFileDump& Demo, const void *parseBuffer, int BufferSize )
{
	CSVCMsg_GameEvent msg;

	if( msg.ParseFromArray( parseBuffer, BufferSize ) )
	{
		int iDescriptor;

		for( iDescriptor = 0; iDescriptor < Demo.m_GameEventList.descriptors().size(); iDescriptor++ )
		{
			const CSVCMsg_GameEventList::descriptor_t& Descriptor = Demo.m_GameEventList.descriptors( iDescriptor );

			if( Descriptor.eventid() == msg.eventid() )
				break;
		}

		if( iDescriptor == Demo.m_GameEventList.descriptors().size() )
		{
			printf( "%s", msg.DebugString() );
		}
		else
		{
			int numKeys = msg.keys().size();
			const CSVCMsg_GameEventList::descriptor_t& Descriptor = Demo.m_GameEventList.descriptors( iDescriptor );

			printf( "%s eventid:%d %s\n", Descriptor.name().c_str(), msg.eventid(),
				msg.has_event_name() ? msg.event_name().c_str() : "" );

			for( int i = 0; i < numKeys; i++ )
			{
				const CSVCMsg_GameEventList::key_t& Key = Descriptor.keys( i );
				const CSVCMsg_GameEvent::key_t& KeyValue = msg.keys( i );

				printf(" %s: ", Key.name().c_str() );

				if( KeyValue.has_val_string() )
					printf( "%s ", KeyValue.val_string().c_str() );
				if( KeyValue.has_val_float() )
					printf( "%f ", KeyValue.val_float() );
				if( KeyValue.has_val_long() )
					printf( "%d ", KeyValue.val_long() );
				if( KeyValue.has_val_short() )
					printf( "%d ", KeyValue.val_short() );
				if( KeyValue.has_val_byte() )
					printf( "%d ", KeyValue.val_byte() );
				if( KeyValue.has_val_bool() )
					printf( "%d ", KeyValue.val_bool() );
				if( KeyValue.has_val_uint64() )
					printf( "%lld ", KeyValue.val_uint64() );

				printf( "\n" );
			}
		}
	}
}

static std::string GetNetMsgName( int Cmd )
{
	if( NET_Messages_IsValid( Cmd ) )
	{
		return NET_Messages_Name( ( NET_Messages )Cmd );
	}
	else if( SVC_Messages_IsValid( Cmd ) )
	{
		return SVC_Messages_Name( ( SVC_Messages )Cmd );
	}

	assert( 0 );
	return "NETMSG_???";
}


void CDemoFileDump::DumpDemoPacket( const std::string& buf )
{
	size_t index = 0;
	int currentTick = -1;
	while( index < buf.size() )
	{
		int Cmd = ReadVarInt32( buf, index );
		uint32 Size = ReadVarInt32( buf, index );

		if( index + Size > buf.size() )
		{
			const std::string& strName = GetNetMsgName( Cmd );

			fatal_errorf( "buf.ReadBytes() failed. Cmd:%d '%s' \n", Cmd, strName.c_str() );
		}

		switch( Cmd )
		{
#define HANDLE_NetMsg( _x )		case net_ ## _x: PrintNetMessage< CNETMsg_ ## _x, net_ ## _x >( *this, &buf[ index ], Size ); break
#define HANDLE_SvcMsg( _x )		case svc_ ## _x: PrintNetMessage< CSVCMsg_ ## _x, svc_ ## _x >( *this, &buf[ index ], Size ); break

		default:
			printf( "WARNING. DumpUserMessage(): Unknown netmessage %d.\n", Cmd );
			break;

		HANDLE_NetMsg( NOP );            	// 0
		HANDLE_NetMsg( Disconnect );        // 1
		HANDLE_NetMsg( File );              // 2
		HANDLE_NetMsg( SplitScreenUser );   // 3
		//HANDLE_NetMsg( Tick );              // 4
		HANDLE_NetMsg( StringCmd );         // 5
		HANDLE_NetMsg( SetConVar );         // 6
		HANDLE_NetMsg( SignonState );       // 7
		HANDLE_SvcMsg( ServerInfo );        // 8
		//HANDLE_SvcMsg( SendTable );         // 9
		HANDLE_SvcMsg( ClassInfo );         // 10
		HANDLE_SvcMsg( SetPause );          // 11
		HANDLE_SvcMsg( CreateStringTable ); // 12
		HANDLE_SvcMsg( UpdateStringTable ); // 13
		HANDLE_SvcMsg( VoiceInit );         // 14
		HANDLE_SvcMsg( VoiceData );         // 15
		HANDLE_SvcMsg( Print );             // 16
		HANDLE_SvcMsg( Sounds );            // 17
		HANDLE_SvcMsg( SetView );           // 18
		HANDLE_SvcMsg( FixAngle );          // 19
		HANDLE_SvcMsg( CrosshairAngle );    // 20
		HANDLE_SvcMsg( BSPDecal );          // 21
		HANDLE_SvcMsg( SplitScreen );       // 22
		HANDLE_SvcMsg( UserMessage );       // 23
		//$ HANDLE_SvcMsg( EntityMessage ); // 24
		HANDLE_SvcMsg( GameEvent );         // 25
//		HANDLE_SvcMsg( PacketEntities );    // 26
		HANDLE_SvcMsg( TempEntities );      // 27
		HANDLE_SvcMsg( Prefetch );          // 28
		HANDLE_SvcMsg( Menu );              // 29
		HANDLE_SvcMsg( GameEventList );     // 30
		HANDLE_SvcMsg( GetCvarValue );      // 31

#undef HANDLE_SvcMsg
#undef HANDLE_NetMsg
		case svc_SendTable:
			{
				const void *parseBuffer = &buf[ index ];
				Size;
				CSVCMsg_SendTable msg;
				if(msg.ParseFromArray( parseBuffer, Size))
				{
					ReceiveTableClass receiveTable;
					receiveTable.name = msg.net_table_name();
					receiveTable.needsDecode = msg.needs_decoder();
					for(int i = 0; i < msg.props_size(); i++)
					{
						ReceiveTableProperty receiveProperty;
						const CSVCMsg_SendTable_sendprop_t prop = msg.props(i);
						//CSVCMsg_SendTable_sendprop_t::
						if(prop.has_type())
							receiveProperty.type = prop.type();
						if(prop.has_dt_name())
							receiveProperty.dt_name = prop.dt_name();
						if(prop.has_flags())
							receiveProperty.flags = prop.flags();
						if(prop.has_high_value())
							receiveProperty.high_value = prop.high_value();
						if(prop.has_low_value())
							receiveProperty.low_value = prop.low_value();
						if(prop.has_num_bits())
							receiveProperty.num_bits = prop.num_bits();
						if(prop.has_num_elements())
							receiveProperty.num_elements = prop.num_elements();
						if(prop.has_priority())
							receiveProperty.priority = prop.priority();
						if(prop.has_var_name())
							receiveProperty.var_name = prop.var_name();
						receiveProperty.originalTable = receiveTable.name;

						if(receiveProperty.flags & EXCLUDE)
							receiveTable.exclusions.push_back(receiveProperty);
						else
							receiveTable.props.push_back(receiveProperty);
												
					}
					dotaClassContainer.dotaClasses[receiveTable.name] = receiveTable;
				}
			}
			break;
		case net_Tick:
			{
				const void *parseBuffer = &buf[ index ];
				Size;
				CNETMsg_Tick msg;
				if(msg.ParseFromArray( parseBuffer, Size))
				{
					//printf( "---- %s (%d bytes) -----------------\n", msg.GetTypeName().c_str() , Size );
					currentTick = msg.tick();
					printf("Tick: %d\n", currentTick);
				}
			}
			break;
		case svc_PacketEntities:
			{
				const void *parseBuffer = &buf[ index ];
				Size;
				CSVCMsg_PacketEntities msg;

				if( msg.ParseFromArray( parseBuffer, Size ) )
				{
					bool isDelta = msg.is_delta();
					int numEntries = msg.updated_entries();
					std::string entityData = msg.entity_data();

					printf( "---- %s (%d bytes) -----------------\n", msg.GetTypeName().c_str() , Size );
					printf("updated_entries: %d\n", numEntries);
					printf("is_delta: %s\n", isDelta ? "true" : "false");
					if(isDelta)
						printf("delta_from: %d\n", msg.delta_from());
					printf( "entity_data: ");

					unsigned int bitLength = 10;
					unsigned int flag = 1 << (bitLength-1);
					unsigned int bits = 0;
					/*std::map<int,std::vector<int>>* tickids = &ids[currentTick];
					for(unsigned int i = 0; i < 2048; i++)
					{
						if(isDelta)
						{
							int prevTick = msg.delta_from();
							if(ids[prevTick].find(i) != ids[prevTick].end())
								if(ids[prevTick][i].size() > 0)
									(*tickids)[i].clear();
						}
						else
							(*tickids)[entities[i]].clear();
					}*/
					std::vector<int> bitadresses;
					if(isDelta)
					{
						for(unsigned int i = 0; i < entityData.size(); i++)
						{
							unsigned char byte = ((unsigned char*)entityData.c_str())[i];
							unsigned int uinbyte = byte;
							printf(" %02X", byte);
						

							for(unsigned int b = 0; b < 8; b++)
							{
								bits >>= 1;
								bits += (uinbyte << (bitLength-1) - b) & flag;

								if( i*8 + b >= bitLength && bits == 221)
								{
									bitadresses.push_back(i*8 + b - bitLength);
								}
							}
						}
					}
					for(int i = 0; i < bitadresses.size(); i++)
					{
						printf("\nBitadress:%d",bitadresses[i]);
					}
					printf("\n");
				}

				break;
			}
		}
		index += Size;
	}
}

static bool DumpDemoStringTable( CDemoFileDump& Demo, const CDemoStringTables& StringTables )
{
	for( int i = 0; i < StringTables.tables().size(); i++ )
	{
		const CDemoStringTables::table_t& Table = StringTables.tables( i );

		printf( "#%d %s flags:0x%x (%d Items) %d bytes\n",
			i, Table.table_name().c_str(), Table.table_flags(),
			Table.items().size() + Table.items_clientside().size(), Table.ByteSize() );

		bool bIsActiveModifiersTable = !strcmp( Table.table_name().c_str(), "ActiveModifiers" );
		bool bIsUserInfo = !strcmp( Table.table_name().c_str(), "userinfo" );

		// Only spew out the stringtables (really big) if verbose is on.
		for( int itemid = 0; itemid < Table.items().size(); itemid++ )
		{
			const CDemoStringTables::items_t& Item = Table.items( itemid );

			if( bIsActiveModifiersTable )
			{
				CDOTAModifierBuffTableEntry Entry;

				if( Entry.ParseFromString( Item.data() ) )
				{
					std::string EntryStr = Entry.DebugString();
					printf( "    #%d %s", itemid, EntryStr.c_str() );
					continue;
				}
			}
			else if( bIsUserInfo && Item.data().size() == sizeof( player_info_s ) )
			{
				const player_info_s *pPlayerInfo = ( const player_info_s * )&Item.data()[ 0 ];

				printf("    xuid:%lld name:%s userID:%d guid:%s friendsID:%d friendsName:%s fakeplayer:%d ishltv:%d filesDownloaded:%d\n",
					pPlayerInfo->xuid, pPlayerInfo->name, pPlayerInfo->userID, pPlayerInfo->guid, pPlayerInfo->friendsID,
					pPlayerInfo->friendsName, pPlayerInfo->fakeplayer, pPlayerInfo->ishltv, pPlayerInfo->filesDownloaded );
			}

			printf( "    #%d '%s' (%d bytes)\n", itemid, Item.str().c_str(), Item.data().size() );
		}

		for( int itemid = 0; itemid < Table.items_clientside().size(); itemid++ )
		{
			const CDemoStringTables::items_t& Item = Table.items_clientside( itemid );

			printf( "    %d. '%s' (%d bytes)\n", itemid, Item.str().c_str(), Item.data().size() );
		}
	}

	return true;
}

void CDemoFileDump::PrintDemoHeader( EDemoCommands DemoCommand, int tick, int size, int uncompressed_size )
{
	const std::string& DemoCommandName = EDemoCommands_Name( DemoCommand );

	printf( "==== #%d: Tick:%d '%s' Size:%d UncompressedSize:%d ====\n",
		m_nFrameNumber, tick, DemoCommandName.c_str(), size, uncompressed_size );
}

template < class DEMCLASS >
void PrintDemoMessage( CDemoFileDump& Demo, bool bCompressed, int tick, int& size, int& uncompressed_size )
{
	DEMCLASS Msg;

	if( Demo.m_demofile.ReadMessage( &Msg, bCompressed, &size, &uncompressed_size ) )
	{
		Demo.PrintDemoHeader( Msg.GetType(), tick, size, uncompressed_size );

		Demo.MsgPrintf( Msg, size, "%s", Msg.DebugString().c_str() );
	}
}

template <>
void PrintDemoMessage<CDemoStringTables_t>( CDemoFileDump& Demo, bool bCompressed, int tick, int& size, int& uncompressed_size )
{
	CDemoStringTables_t Msg;

	if( Demo.m_demofile.ReadMessage( &Msg, bCompressed, &size, &uncompressed_size ) )
	{
		Demo.PrintDemoHeader( Msg.GetType(), tick, size, uncompressed_size );

		DumpDemoStringTable( Demo, Msg );
	}
}

void CDemoFileDump::DoDump()
{
	bool bStopReading = false;

	for( m_nFrameNumber = 0; !bStopReading; m_nFrameNumber++ )
	{
		int tick = 0;
		int size = 0;
		bool bCompressed;
		int uncompressed_size = 0;

		if( m_demofile.IsDone() )
			break;

		EDemoCommands DemoCommand = m_demofile.ReadMessageType( &tick, &bCompressed );

		switch( DemoCommand )
		{
#define HANDLE_DemoMsg( _x )	case DEM_ ## _x: PrintDemoMessage< CDemo ## _x ## _t >( *this, bCompressed, tick, size, uncompressed_size ); break

		HANDLE_DemoMsg( FileHeader );
		HANDLE_DemoMsg( FileInfo );
		HANDLE_DemoMsg( Stop );
		HANDLE_DemoMsg( SyncTick );
		HANDLE_DemoMsg( ConsoleCmd );
		//HANDLE_DemoMsg( SendTables );
		HANDLE_DemoMsg( ClassInfo );
		HANDLE_DemoMsg( StringTables );
		HANDLE_DemoMsg( UserCmd );
		HANDLE_DemoMsg( CustomDataCallbacks );
		HANDLE_DemoMsg( CustomData );

#undef HANDLE_DemoMsg

		case DEM_FullPacket:
			{
				CDemoFullPacket_t FullPacket;

				if( m_demofile.ReadMessage( &FullPacket, bCompressed, &size, &uncompressed_size ) )
				{
					PrintDemoHeader( DemoCommand, tick, size, uncompressed_size );

					// Spew the stringtable
					DumpDemoStringTable( *this, FullPacket.string_table() );

					// Ok, now the packet.
					ids.clear();
					DumpDemoPacket( FullPacket.packet().data() );
				}
			}
			break;
		case DEM_SendTables:
			{
				CDemoSendTables_t Msg;

				if( m_demofile.ReadMessage( &Msg, bCompressed, &size, &uncompressed_size ) )
				{
					PrintDemoHeader( Msg.GetType(), tick, size, uncompressed_size );

					//Demo.MsgPrintf( Msg, size, "%s", Msg.DebugString().c_str() );
					DumpDemoPacket(Msg.data());
				}
				dotaClassContainer.Traverse();
				unsigned int propcount = dotaClassContainer.PropCount();
			}
			break;
		case DEM_Packet:
		case DEM_SignonPacket:
			{
				CDemoPacket_t Packet;

				if( m_demofile.ReadMessage( &Packet, bCompressed, &size, &uncompressed_size ) )
				{
					PrintDemoHeader( DemoCommand, tick, size, uncompressed_size );

					DumpDemoPacket( Packet.data() );
				}
			}
			break;

		default:
		case DEM_Error:
			bStopReading = true;
			fatal_errorf( "Shouldn't ever get this demo command?!? %d\n", DemoCommand );
			break;
		}

		if( _kbhit() )
		{
			int ch = toupper( _getch() );

			if( ch == 'Q' )
				break;
		}
	}
}

