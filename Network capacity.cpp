// Pauls Brikmanis 5.grupa 201RDB002
// 7.variants 2.Laboratorijas darbs
#include <iostream>
#include <typeinfo>
using namespace std;

class OverflowException
{
public:
	OverflowException()
	{
		cout << endl
			 << "Exception created!" << endl;
	}
	OverflowException(const OverflowException &)
	{
		cout << "Exception copied!" << endl;
	}
	~OverflowException()
	{
		cout << "Exception finished!" << endl;
	}
};

class Computer
{
protected:
	string procesors;
	float frekvence;
	short operativas_atminas_apjoms;

public:
	Computer();
	Computer(string, float, short);

	virtual ~Computer()
	{
		cout << "Message from the \"Computer\" - destroyed!" << endl;
	}

	virtual void Print() const;

	string Get_procesors() const;
	float Get_frekvence() const;
	short Get_operativas_atminas_apjoms() const;

	void Set_procesors(string);
	void Set_frekvence(float);
	void Set_operativas_atminas_apjoms(short);
};
class NetComputer : public Computer
{
private:
	string IP_adrese;

public:
	NetComputer() : Computer(), IP_adrese()
	{
	}
	NetComputer(string, float, short, string);
	virtual ~NetComputer()
	{
		cout << endl
			 << "Message from the \"DisplayPoint\" - destroyed!" << endl;
	}
	string GetIP_adrese() const
	{
		return IP_adrese;
	}
	void SetIP_adrese(string IP_adrese)
	{
		this->IP_adrese = IP_adrese;
	}
	virtual void Print() const;
};

class ComputerNetwork
{
private:
	typedef NetComputer *NCPointer;
	NCPointer *Nodes;
	static const unsigned int DEFAULT_MAX_LENGTH = 5;
	unsigned int MaxLength;
	unsigned int Ram;	   // Lenght nomainīju uz Ram
	unsigned short MaxRam; // Te kjip bija usnigned int LineColor un viņš teica, ka jāņem nost, es nez, ko likt, ieliku šo
public:
	ComputerNetwork() : MaxLength(DEFAULT_MAX_LENGTH), Ram(0), MaxRam(0)
	{
		Nodes = new NCPointer[MaxLength];
	}
	ComputerNetwork(unsigned int MaxLength, unsigned short MaxRam) : MaxLength(MaxLength), Ram(0)
	{
		this->MaxRam = MaxRam; // Ganjau te dirsā
		Nodes = new NCPointer[MaxLength];
	}
	~ComputerNetwork();
	static unsigned int GetDefaultMaxRam()
	{
		return DEFAULT_MAX_LENGTH;
	}
	int GetRam() const
	{
		return Ram;
	}
	void AddNode(const NetComputer &);
	void Print() const;
	short GetMaxRam();
};

Computer::Computer() : procesors(""), frekvence(0.0), operativas_atminas_apjoms(0) {}

Computer::Computer(string a, float b, short c)
{
	procesors = a;
	frekvence = b;
	operativas_atminas_apjoms = c;
}

inline void Computer::Print() const
{
	cout << "procesors = " << procesors << endl;
	cout << "frekvence = " << frekvence << endl;
	cout << "operativas_atminas_apjoms = " << operativas_atminas_apjoms << endl;
}

inline string Computer::Get_procesors() const
{
	return procesors;
}
inline float Computer::Get_frekvence() const
{
	return frekvence;
}
inline short Computer::Get_operativas_atminas_apjoms() const
{
	return operativas_atminas_apjoms;
}

inline void Computer::Set_procesors(string t)
{
	this->procesors = t;
}
inline void Computer::Set_frekvence(float t)
{
	this->frekvence = t;
}
inline void Computer::Set_operativas_atminas_apjoms(short t)
{
	this->operativas_atminas_apjoms = t;
}
NetComputer::NetComputer(string a, float b, short c, string IP_adreseZ) : Computer(a, b, c)
{
	IP_adrese = IP_adreseZ;
}

inline void NetComputer::Print() const
{
	Computer::Print();
	cout << ", IP_adrese = " << IP_adrese;
}

ComputerNetwork::~ComputerNetwork()
{
	for (unsigned int i = 0; i < Ram; i++)
		delete Nodes[i];
	delete[] Nodes;
}
void ComputerNetwork::Print() const
{
	cout << "\nMax Ram ir: " << MaxRam << "." << endl // šeit linecolor vietā arī ieliku
		 << "Line's nodes:" << endl;
	for (unsigned int i = 0; i < Ram; i++)
	{
		cout << (i + 1) << ". ";
		Nodes[i]->Print();
		cout << "." << endl;
	}
}
void ComputerNetwork::AddNode(const NetComputer &Node)
{
	if (Ram == MaxRam)
		throw OverflowException();
	else
		Nodes[Ram++] = new NetComputer(
			Node.Get_procesors(), Node.Get_frekvence(), Node.Get_operativas_atminas_apjoms(), Node.GetIP_adrese());
}

short ComputerNetwork::GetMaxRam()
{
	short maxRam = Nodes[0]->Get_operativas_atminas_apjoms();
	for (int i = 1; i < Ram; i++)
	{
		if (Nodes[i]->Get_operativas_atminas_apjoms() > maxRam)
		{
			maxRam = Nodes[i]->Get_operativas_atminas_apjoms();
		}
	}
	return maxRam;
}

int main(void)
{
	ComputerNetwork *Line = new ComputerNetwork(3, 5);
	NetComputer *D1 = new NetComputer("string1", 1.1, 1, "string1");
	NetComputer D2("string2", 2.2, 2, "string2");

	try
	{
		Line->AddNode(*D1);
		cout << "\nNew node has been added successfully!" << endl;
	}
	catch (const OverflowException &)
	{
		cout << "*** Error: maximal length exceeded! ***" << endl;
	}
	catch (...)
	{
		cout << "Unknown error!" << endl;
	}
	delete D1;

	cout << "\nDefault maximal length (from CLASS): " << ComputerNetwork::GetDefaultMaxRam() << "." << endl;
	cout << "Default Ram length (from OBJECT): " << Line->GetDefaultMaxRam() << "." << endl;
	cout << "Maximal Ram: " << Line->GetMaxRam() << "." << endl;
	cout << "Current Ram: " << Line->GetRam() << "." << endl;

	try
	{
		Line->AddNode(D2);
		cout << "\nNew node has been added successfully!" << endl;
	}
	catch (const OverflowException &)
	{
		cout << "*** Error: maximal length exceeded! ***" << endl;
	}
	catch (...)
	{
		cout << "Unknown error!" << endl;
	}

	try
	{
		Line->AddNode(D2);
		cout << "\nNew node has been added successfully!" << endl;
	}
	catch (const OverflowException &)
	{
		cout << "*** Error: maximal length exceeded! ***" << endl;
	}
	catch (...)
	{
		cout << "Unknown error!" << endl;
	}

	Line->Print();

	cout << "Max Ram: " << Line->GetMaxRam() << endl;
	cout << endl;

	cout << endl
		 << "Broken line deletion:";
	delete Line;

	cin.get();
	return 0;
}