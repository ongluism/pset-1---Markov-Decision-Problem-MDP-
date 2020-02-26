// (0)a: Only myself
// (0)b: stack overflow, MIT website

// 1(a): state space size = N_s = 5*6 - 4 = 26 
// 1(b): action space size = N_a = 5 

//2(a), 2(b): See Below Code

#include <string>
#include <iostream>
#include <cmath>
//global variables
const double GAMMA_FACT = 0; //discount factor
const double ERROR_PROB = 0.3;	//error probability

								// 1(a)
								// 1(b) (No class is created for action space. Only strings "N" "S" "W" "E" directions)
class s_states
{
	//has number of states
	//which state robot is in
public:
	s_states(int x_pos, int y_pos)
	{
		mx_pos = x_pos;
		my_pos = y_pos;
	}

	void setState_x(int x)
	{
		mx_pos = x;
	}

	int getState_x()
	{
		return mx_pos;
	}

	void setState_y(int y)
	{
		my_pos = y;
	}

	int getState_y()
	{
		return my_pos;
	}

private:
	int mx_pos;
	int my_pos;

};

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
/*
Actions: Move up (North) = "N"
Move down (South) = "S"
Move left (East) = "E"
Move right (West) = "W"
Dont move = "X"
*/

// 3(a)
string my_array[6][5] =
{
	{ "E", "E", "E", "E" , "E" },   /*  initializers for row indexed by 0 */
{ "E", "E", "E", "E" , "E" },   /*  initializers for row indexed by 1 */
{ "E", "E", "E", "E" , "E" },  /*  initializers for row indexed by 2 */
{ "E", "E", "E", "E" , "E" },
{ "E", "E", "E", "E" , "E" },
{ "E", "E", "E", "E" , "E" }
};
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
// 3(b)
void input_policy()
{
	string val;

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (((j > 0 && j < 2) && (i > 0 && i < 2)) || ((j > 0 && j < 2) && (i > 2 && i < 4)) ||
				((j > 1 && j < 3) && (i > 0 && i < 2)) || ((j > 1 && j < 3) && (i > 2 && i < 4)))
			{
				my_array[i][j] = '#';
			}
			else
			{
				cout << "enter action:";
				cin >> val;
				my_array[i][j] = val;
			}
		}

	}
}
// 3(b)
void print_policy()
{
	int i, j;
	for (i = 0; i < 6; ++i)
	{
		for (j = 0; j < 5; ++j)
		{
			if (((j > 0 && j < 2) && (i > 0 && i < 2)) || ((j > 0 && j < 2) && (i > 2 && i < 4)) ||
				((j > 1 && j < 3) && (i > 0 && i < 2)) || ((j > 1 && j < 3) && (i > 2 && i < 4)))
				cout << my_array[i][j] << ' ';	//'#' represents an obstacle
			else
				cout << my_array[i][j] << ' ';
		}
		cout << endl;
	}
}

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
// 2(b)
int reward(s_states s)
{
	if (s.getState_x() == 2 && s.getState_y() == 0)
		return 10;
	if (s.getState_x() == 2 && s.getState_y() == 2)
		return 1;
	if (s.getState_x() == 4)
		return -100;
}
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------
//return transition error probability
//given three inputs: current state, an action, next state
//------------------------------------------------------------------------------------

//1(c) and 2(a)
double transition_probability(s_states s_current, string a_act, s_states s_next)
{
	srand(time(NULL));
	double num = (100 - (ERROR_PROB * 100));
	double success_num = (rand() % 100) < num;


	const int X_OBSTACLE1 = 1;
	const int X_OBSTACLE2 = 2;
	const int X_OBSTACLE3 = 1;
	const int X_OBSTACLE4 = 2;

	const int Y_OBSTACLE1 = 1;
	const int Y_OBSTACLE2 = 1;
	const int Y_OBSTACLE3 = 3;
	const int Y_OBSTACLE4 = 3;

	int x_cur = s_current.getState_x();
	int y_cur = s_current.getState_y();

	int x_nxt = s_next.getState_x();
	int y_nxt = s_next.getState_y();

	//must be inside 5 x 6 grid
	if (x_cur < 0 || x_cur > 4 || y_cur < 0 || y_cur > 5 ||
		x_nxt < 0 || x_nxt > 4 || y_nxt < 0 || y_nxt > 5)
	{
		cout << "Invalid current and/or next state" << endl;
		//exit(0);
	}

	//cannot occupy space with obstacle
	if ((x_cur == X_OBSTACLE1 && y_cur == Y_OBSTACLE1) || (x_cur == X_OBSTACLE2 && y_cur == Y_OBSTACLE2) ||
		(x_cur == X_OBSTACLE3 && y_cur == Y_OBSTACLE3) || (x_cur == X_OBSTACLE4 && y_cur == Y_OBSTACLE4) ||
		(x_nxt == X_OBSTACLE1 && y_nxt == Y_OBSTACLE1) || (x_nxt == X_OBSTACLE2 && y_nxt == Y_OBSTACLE2) ||
		(x_nxt == X_OBSTACLE3 && y_nxt == Y_OBSTACLE3) || (x_nxt == X_OBSTACLE4 && y_nxt == Y_OBSTACLE4))
	{
		cout << "Warning: Either current or next state occupies space with obstacle" << endl;
		//exit(0);
	}


	if (a_act == "X")	//choose to NOT move
	{
		cout << "no moving = no error" << endl;
		return 0;
	}

	if (x_nxt > x_cur)	//robot moving to right 
	{
		if (x_nxt > x_cur + 1)//makes sure current and next state are close enough
			return 0;
		else if (y_cur == y_nxt)//same y-axis level
		{
			if (a_act == "E" && success_num == 1)//only action that gets us to next state
			{
				if (((x_nxt != X_OBSTACLE1) && (y_nxt != Y_OBSTACLE1)) &&
					((x_nxt != X_OBSTACLE2) && (y_nxt != Y_OBSTACLE2)) &&
					((x_nxt != X_OBSTACLE3) && (y_nxt != Y_OBSTACLE3)) &&
					((x_nxt != X_OBSTACLE4) && (y_nxt != Y_OBSTACLE4)))
				{
					cout << "Success!" << endl;
					cout << "Transition probability is: " << (1 - ERROR_PROB) << endl;
					return (1 - ERROR_PROB);
				}
				else
				{
					cout << "Hit wall to right, stay in place!" << endl;
					cout << "Transition probability is: " << 0 << endl;
					return 0;
				}
			}
			if (success_num == 0)
			{
				if (((x_nxt != X_OBSTACLE1) && (y_nxt != Y_OBSTACLE1)) &&
					((x_nxt != X_OBSTACLE2) && (y_nxt != Y_OBSTACLE2)) &&
					((x_nxt != X_OBSTACLE3) && (y_nxt != Y_OBSTACLE3)) &&
					((x_nxt != X_OBSTACLE4) && (y_nxt != Y_OBSTACLE4)))
				{
					cout << "success by error!" << endl;
					return (ERROR_PROB / 4);	//still can get next state by error     //'4' signifies  error i ssplit btwn 4 directions
				}
				else
				{
					cout << "hit wall, stay in place!" << endl;
					cout << "Transition probability is: " << 0 << endl;
					return 0;
				}
			}
			if (success_num == 1 && (a_act == "S" || a_act == "N" || a_act == "W"))
			{
				cout << "Transition probability is: " << 0 << endl;
				return 0;
			}
		}
		else
			return 0;	//cannot move diagonally
	}

	if (x_nxt < x_cur)	//robot moving to left
	{
		if (x_nxt < x_cur - 1)
			return 0;
		else if (y_cur == y_nxt)//same y-axis level
		{
			if (a_act == "W" && success_num == 1)//only action that gets us to next state
			{
				if (((x_nxt != X_OBSTACLE1) && (y_nxt != Y_OBSTACLE1)) &&
					((x_nxt != X_OBSTACLE2) && (y_nxt != Y_OBSTACLE2)) &&
					((x_nxt != X_OBSTACLE3) && (y_nxt != Y_OBSTACLE3)) &&
					((x_nxt != X_OBSTACLE4) && (y_nxt != Y_OBSTACLE4)))
				{
					cout << "success!" << endl;
					cout << "Transition probability is: " << (1 - ERROR_PROB) << endl;
					return (1 - ERROR_PROB);
				}
				else
				{
					cout << "Hit wall to left, stay in place!" << endl;
					cout << "Transition probability is: " << 0 << endl;
					return 0;
				}
			}
			if (success_num == 0)
			{
				if (((x_nxt != X_OBSTACLE1) && (y_nxt != Y_OBSTACLE1)) &&
					((x_nxt != X_OBSTACLE2) && (y_nxt != Y_OBSTACLE2)) &&
					((x_nxt != X_OBSTACLE3) && (y_nxt != Y_OBSTACLE3)) &&
					((x_nxt != X_OBSTACLE4) && (y_nxt != Y_OBSTACLE4)))
				{
					cout << "success by error!" << endl;
					return (ERROR_PROB / 4);	//can still get to next state by error
				}
				else
				{
					cout << "hit wall, stay in place!" << endl;
					cout << "Transition probability is: " << 0 << endl;
					return 0;
				}
			}
			if (success_num == 1 && (a_act == "S" || a_act == "E" || a_act == "N"))
			{
				cout << "Transition probability is: " << 0 << endl;
				return 0;
			}
		}
		else
			return 0;	//cannot move diagonally
	}

	if (y_nxt > y_cur)	//robot moving up 
	{
		if (y_nxt > y_cur + 1)
			return 0;
		else if (x_cur == x_nxt)//same x-axis level
		{
			if (a_act == "N" && success_num == 1)//only action that gets us to next state
			{
				if (((x_nxt != X_OBSTACLE1) && (y_nxt != Y_OBSTACLE1)) &&
					((x_nxt != X_OBSTACLE2) && (y_nxt != Y_OBSTACLE2)) &&
					((x_nxt != X_OBSTACLE3) && (y_nxt != Y_OBSTACLE3)) &&
					((x_nxt != X_OBSTACLE4) && (y_nxt != Y_OBSTACLE4)))
				{
					cout << "success!" << endl;
					cout << "Transition probability is: " << (1 - ERROR_PROB) << endl;
					return (1 - ERROR_PROB);
				}
				else
				{
					cout << "Hit wall to top, stay in place!" << endl;
					cout << "Transition probability is: " << 0 << endl;
					return 0;
				}
			}
			if (success_num == 0)
			{

				if (((x_nxt != X_OBSTACLE1) && (y_nxt != Y_OBSTACLE1)) &&
					((x_nxt != X_OBSTACLE2) && (y_nxt != Y_OBSTACLE2)) &&
					((x_nxt != X_OBSTACLE3) && (y_nxt != Y_OBSTACLE3)) &&
					((x_nxt != X_OBSTACLE4) && (y_nxt != Y_OBSTACLE4)))
				{
					cout << "success by error!" << endl;
					return (ERROR_PROB / 4);	//can still get to next state by error
				}
				else
				{
					cout << "hit wall, stay in place!" << endl;
					cout << "Transition probability is: " << 0 << endl;
					return 0;
				}
			}
			if (success_num == 1 && (a_act == "S" || a_act == "E" || a_act == "W"))
			{
				cout << "Transition probability is: " << 0 << endl;
				return 0;
			}
		}
		else
			return 0;	//cannot move diagonally
	}

	if (y_nxt < y_cur)	//robot moving down
	{
		if (y_nxt < y_cur - 1)
			return 0;
		else if (x_cur == x_nxt)//same x-axis level
		{
			if (a_act == "S" && success_num == 1)//only action that gets us to next state
			{
				if (((x_nxt != X_OBSTACLE1) && (y_nxt != Y_OBSTACLE1)) &&
					((x_nxt != X_OBSTACLE2) && (y_nxt != Y_OBSTACLE2)) &&
					((x_nxt != X_OBSTACLE3) && (y_nxt != Y_OBSTACLE3)) &&
					((x_nxt != X_OBSTACLE4) && (y_nxt != Y_OBSTACLE4)))
				{
					cout << "success!" << endl;
					cout << "Transition probability is: " << (1 - ERROR_PROB) << endl;
					return (1 - ERROR_PROB);
				}
				else
				{
					cout << "Hit wall to bottom, stay in place!" << endl;
					cout << "Transition probability is: " << 0 << endl;
					return 0;
				}
			}
			if (success_num == 0)
			{
				if (((x_nxt != X_OBSTACLE1) && (y_nxt != Y_OBSTACLE1)) &&
					((x_nxt != X_OBSTACLE2) && (y_nxt != Y_OBSTACLE2)) &&
					((x_nxt != X_OBSTACLE3) && (y_nxt != Y_OBSTACLE3)) &&
					((x_nxt != X_OBSTACLE4) && (y_nxt != Y_OBSTACLE4)))
				{
					cout << "success by error!" << endl;
					return (ERROR_PROB / 4);	//can still get to next state by error
				}
				else
				{
					cout << "hit wall, stay in place!" << endl;
					cout << "Transition probability is: " << 0 << endl;
					return 0;
				}
			}
			if (success_num == 1 && (a_act == "N" || a_act == "E" || a_act == "W"))
			{
				cout << "Transition probability is: " << 0 << endl;
				return 0;
			}
		}
		else
			return 0;	//cannot move diagonally
	}

	cout << "HMMMMM" << endl;
}
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------

//top level function for testing (see example of test run below)
int main()
{
	cout << "test_a" << endl;
	s_states cur_state(1, 2); //current state

	cout << "test_b" << endl;
	s_states nxt_state(1, 3);	//next state

	cout << "test_c" << endl;

	transition_probability(cur_state, "down", nxt_state); //output number btwn 0 and 1

	cout << "Done." << endl;

	input_policy(); //user inputs each policy/action for each state s in the 2d array/matrix/grid
	print_policy();
}
