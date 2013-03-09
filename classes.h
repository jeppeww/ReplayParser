#pragma once


#include <string>
#include <vector>
#include <map>

class SendTableClass;

enum FLAGS
{
    UNSIGNED	= 1 <<  0, // unsigned integer
    COORD		= 1 <<  1, // fp/vector treated as world coord (bit count ignored)
    NOSCALE		= 1 <<  2, // for fp, take as-is value
    ROUNDDOWN	= 1 <<  3, // for fp, limit high value to range minus one bit unit
    ROUNDUP		= 1 <<  4, // for fp, limit low  value to range minus one bit unit
    NORMAL		= 1 <<  5, // vector is treated like a normal (valid only for vectors)
    EXCLUDE		= 1 <<  6, // this prop points to another prop to be excluded
    XYZE		= 1 <<  7, // use XYZ/exponent encoding for vectors
    INSIDEARRAY	= 1 <<  8, // prop is inside array ("shouldn't be put in flattened prop list" (?))
    ALWAYSPROXY	= 1 <<  9, // set for data table props using a default proxy type
    VECTORELEM	= 1 << 10, // set for fields set often so they get a small index in sendtable
    COLLAPSIBLE	= 1 << 11, // set if prop is datatable with zero offset that doesn't change pointer (?)
    COORDMP		= 1 << 12, // like coord, but for multiplayer games
    COORDMPLLOW	= 1 << 13, // like coord, but fractional component gets 3 bits, not five
    COORDMPINT	= 1 << 14, // like coord, but rounded to integral boundaries
	CELLCOORD	= 1 << 15, // Nothing for some reason?
	CELLCOORDLOW= 1 << 16, // Only in vecOrigin and vecOrigin[2]
	CELLCOORDINT= 1 << 17, // seems to bump properties to just above p = 128
	CHANGESOFTEN= 1 << 18, // Changes ofte, so bump it up
	SERVERSTUFF	= 1 << 19, //Some server stuff
    UNKOWN		= 0xff00
};


std::string getFlags(int flags)
{
	std::string returnString = "";

	int z;
    for (z = 1 << 19; z > 0; z >>= 1)
    {
		FLAGS thisFlag = FLAGS(flags & z);
		switch(thisFlag)
		{
#define HANDLE_FLAG( _x )	case _x: returnString += #_x; returnString += ", ";break
		case 0:
			break;
		HANDLE_FLAG(UNSIGNED);
		HANDLE_FLAG(COORD);
		HANDLE_FLAG(NOSCALE);
		HANDLE_FLAG(ROUNDDOWN);
		HANDLE_FLAG(ROUNDUP);
		HANDLE_FLAG(NORMAL);
		HANDLE_FLAG(EXCLUDE);
		HANDLE_FLAG(XYZE);
		HANDLE_FLAG(INSIDEARRAY);
		HANDLE_FLAG(ALWAYSPROXY);
		HANDLE_FLAG(CHANGESOFTEN);
		HANDLE_FLAG(VECTORELEM);
		HANDLE_FLAG(COLLAPSIBLE);
		HANDLE_FLAG(COORDMP);
		HANDLE_FLAG(COORDMPLLOW);
		HANDLE_FLAG(COORDMPINT);
		HANDLE_FLAG(CELLCOORD);
		HANDLE_FLAG(CELLCOORDLOW);
		HANDLE_FLAG(CELLCOORDINT);
		HANDLE_FLAG(SERVERSTUFF);
		HANDLE_FLAG(UNKOWN);
		default:
			printf("UNKNOWN FLAG BUGGERY");
			break;
		}
    }

	return returnString;
}

typedef enum
{
	DPT_Int=0,
	DPT_Float,
	DPT_Vector,
	DPT_VectorXY,
	DPT_String,
	DPT_Array,	// An array of the base types (can't be of datatables).
	DPT_DataTable,
	DPT_Picture,
	DPT_NUMSendPropTypes
} SendPropType;


class ReceiveTableProperty
{
public:
	ReceiveTableProperty()
	{
		type = -1;
		var_name = "";
		flags = -1;
		priority = -1;
		low_value = -1;
		high_value = -1;
		num_bits = -1;
		num_elements = -1;
		dt_name = "";
		Excluded = false;
	}
public:

	int type;
	std::string var_name;
	int flags;
	int priority;
	int low_value;
	int high_value;
	int num_bits;
	int num_elements;
	std::string dt_name;
	std::string originalTable;
	bool Excluded;
};

class ReceiveTableClass
{
public:
	ReceiveTableClass()
	{
		needsDecode = false;
		totBits = 0;
		baseClass = "";
	}
public:
	std::string name;
	int totBits;
	bool needsDecode;
	std::string baseClass;
	std::vector<ReceiveTableProperty> props;
	std::vector<ReceiveTableProperty> exclusions;
};

class DotaClassContainer
{
public:
	std::map<std::string, ReceiveTableClass> dotaClasses;
	std::map<std::string, ReceiveTableClass> FlattenedTables;

	void Traverse()
	{
		for(auto it = dotaClasses.begin(); it != dotaClasses.end(); it++)
		{
			if(!it->second.needsDecode)
				continue;


			FlattenedTables[it->first] = it->second;
			ReceiveTableClass* Table = &FlattenedTables[it->first];

			auto base = dotaClasses.find(Table->baseClass);
			while(true)
			{
				if(base != dotaClasses.end())
				{
					Table->exclusions.insert(Table->exclusions.begin(), base->second.exclusions.begin(), base->second.exclusions.end());
					base = dotaClasses.find(base->second.baseClass);
				}
				else
					break;
			}

			for(unsigned int i = 0; i < Table->props.size(); i++)
			{
				ReceiveTableProperty* prop = &Table->props[i];
				if(prop->type == DPT_DataTable)  /*&& !(prop->flags & ALWAYSPROXY)*/
				{
					auto dt = dotaClasses.find(prop->dt_name);
					if(dt != dotaClasses.end())
					{
						Table->props.erase(Table->props.begin() + i); //just deleted what prop points to.

						std::vector<ReceiveTableProperty> temp;
						temp.insert(temp.begin(), dt->second.props.begin(), dt->second.props.end());
						std::string tableName = dt->second.name;//temp[k].originalTable;
						
						for(unsigned int k = 0; k < temp.size(); k++) //go trough every property in temp
						{
							std::string varName = temp[k].var_name;
							bool excluded = false;
							for(unsigned int q = 0; q < Table->exclusions.size(); q++) //if property is in exclusions, erase it
							{
								if(Table->exclusions[q].dt_name == tableName && Table->exclusions[q].var_name == varName)
								{
									Table->exclusions[q].Excluded = true;
									if(!excluded) //doing this to properly mark duplicate exclusions
									{
										temp.erase(temp.begin() + k);
										k--;
										excluded = true;
									}
								}
							}
						}
						Table->props.insert(Table->props.begin() + i, temp.begin(), temp.end());
						i--;
					}
					else
					{
						printf("\nMISSED DT PROPERTY!");
					}
				}
			}
			Sort(Table);
			printf("\n\nFlattened %s\n", Table->name.c_str());
			printf("Exclusions:\n");
			for(unsigned int i = 0; i < Table->exclusions.size(); i++)
				printf("%d: %s.%s [%s]\n", i,	Table->exclusions[i].dt_name.c_str(),
												Table->exclusions[i].var_name.c_str(),
												Table->exclusions[i].Excluded ? "Excluded" : "Missed");
			printf("Properties:\n");
			for(unsigned int i = 0; i < Table->props.size(); i++)
				printf("%d: %s.%s  flags: %s\n", i,		Table->props[i].originalTable.c_str(),
														Table->props[i].var_name.c_str(),
														getFlags(Table->props[i].flags).c_str());
		}
	}

	unsigned int PropCount()
	{
		unsigned int count = 0;
		for(auto it = FlattenedTables.begin(); it != FlattenedTables.end(); it++)
		{
			count += it->second.props.size();
		}
		return count;
	}
private:
	void Sort(ReceiveTableClass* _ReceiveTableClass)
	{
		for(unsigned int counts = 0; counts < _ReceiveTableClass->props.size(); counts++)
		{
			for(unsigned int i = 0; i < _ReceiveTableClass->props.size() - counts - 1; i++)
			{
				if(_ReceiveTableClass->props[i].priority > _ReceiveTableClass->props[i + 1].priority || 
					(_ReceiveTableClass->props[i].priority == 128 && _ReceiveTableClass->props[i + 1].flags & CHANGESOFTEN && !(_ReceiveTableClass->props[i].flags & CHANGESOFTEN) )) //sort those flagged with CHANGESOFTEN just above priority 128
				{
					ReceiveTableProperty temp = _ReceiveTableClass->props[i];
					_ReceiveTableClass->props[i] = _ReceiveTableClass->props[i+1];
					_ReceiveTableClass->props[i+1] = temp;
				}
			}
		}
	}
};