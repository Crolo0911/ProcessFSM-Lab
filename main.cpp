#include "Public.h"

MyState State = MyState::MatchPid;
BOOL g_Running = true;
void NextState(bool success, MyState next) {
	State = success ? next : MyState::Exit;
}


int main()
{
	
	while (g_Running)
	{
		switch (State)
		{
		case MyState::MatchPid:
			NextState(GetPid(), MyState::ApplyForMem);
			break;
		case MyState::ApplyForMem:
			NextState(GetMem(), MyState::VerifySome);
			break;
		case MyState::VerifySome:
			NextState(CheckState(), MyState::Work);
			break;
		case MyState::Work:
			NextState(DoWork(), MyState::Exit);
			break;
		case MyState::Exit:
				State = MyState::Exit;
				g_Running = false;
				break;
		default:
			std::cout << "Î´ÖªµÄÊäÈë" << std::endl;
			break;
		}
	}

	return 0;
}