#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

class Elevator
{
	enum Direction{ UP, DOWN };
	Direction direction;

	std::vector<int> requests = {};
 	int min_floor; //Undergroud floor will be shown using negative value
 	int max_floor;
 	int current_floor = 0; //ground floor
 	std::size_t passengers = 0;
 	std::size_t capacity;

 public:
 	Elevator(int min_floor, int max_floor, std::size_t capacity) :
 			min_floor(min_floor),
 			max_floor(max_floor),
 			capacity(capacity)
 			{}
 	~Elevator() {}

 	void start_elevator();

 private:
 	void set_initial_request();
 	void set_request();
 	int check_request(int floor) const;
 	int is_valid_request(int floor);
 	void set_direction(int floor);
 };

void Elevator::set_request() 
{
	std::string dest_floor_str;
 	int dest_floor;
 		
 	std::size_t num_of_reqs = capacity - passengers;
	std::cout << "\n" << num_of_reqs << " passengers can enter in the elevator right now\n";
	
	std::cout << "\nEnter \"GO\" when all passengers are in elevator or there is no one to enter from the floor\n";

 	std::cout << "\nEnter destination floor number.\n";
 	std::cin >> dest_floor_str;
 	if (dest_floor_str != "GO" && dest_floor_str != "Go" &&
 			dest_floor_str != "go" && dest_floor_str != "gO")
 	{
 		std::stringstream sstream(dest_floor_str);
		sstream >> dest_floor;
		
 		int is_valid = is_valid_request(dest_floor);
 		if (is_valid == 0)
 		{
 			if (passengers == 0)
		 	{
 	 			set_direction(dest_floor);
 	 		}
 	 		requests.push_back(dest_floor);
 			passengers++;
		}

		for (std::size_t i = 1; i < num_of_reqs; ++i)
 		{
 			std::cin >> dest_floor_str;
 			if (dest_floor_str == "GO" || dest_floor_str == "Go" ||
 					dest_floor_str == "go" || dest_floor_str == "gO")
 			{
 				break;
 			}

 			std::stringstream sstream(dest_floor_str);
 			sstream >> dest_floor;
 			
 			int is_valid = is_valid_request(dest_floor);
			if (is_valid == 0)
 			{
 				requests.push_back(dest_floor);
 				passengers++;
			}

			if (passengers == capacity)
			{
				std::cout << "No more entry. Elevator is full!!\n";
				break;
			}
		}
 	}
}

int Elevator::check_request(int floor) const
{
 	if (passengers >= capacity)
    {
 		return 1;
 	}
 	else if (passengers != 0 && direction == UP && floor < current_floor)
 	{
 		return 2;
 	}
 	else if (passengers != 0 && direction == DOWN && floor > current_floor)
 	{
 		return 3;
 	}
 	else if (floor > max_floor || floor < min_floor)
 	{
 		return 4;
 	}
 	else
 	{
 		return 0;
 	}
}

int Elevator::is_valid_request(int floor)
{
 	int issue_num = check_request(floor);

 	if (issue_num == 1)
 	{
 		std::cout << "Elevator is Full!!\n";
 	}
 	else if (issue_num == 2)
 	{
 		std::cout << "Elevator is going UP.\n";
 	}
 	else if (issue_num == 3)
 	{
 		std::cout << "Elevator is going DOWN.\n";
 	}
 	else if (issue_num == 4)
 	{
 		std::cout << "This floor does not exist\n";
 	}
 	return issue_num;
}

void Elevator::set_direction(int floor)
{
 	if (floor > current_floor)
 	{
 		direction = UP;
 	}
 	else if (floor < current_floor)
 	{
 		direction = DOWN;
 	}
}

void Elevator::start_elevator()
{
 	std::cout << "\nThe current floor is " << current_floor << " and number of person in elevator are " << passengers <<"\n";

 	//Entering requests for first time
 	set_request(); 
 	std::sort(requests.begin(), requests.end());

 	while (!requests.empty())
 	{
 		if (direction == UP)
 		{
 			current_floor = requests[0];
 		}
 		else if (direction == DOWN)
 		{
 			current_floor = requests[requests.size() - 1];
 		}

 		auto curr_floor_req = std::find(requests.begin(), requests.end(), current_floor);
 		while (curr_floor_req != requests.end())
 		{
 			requests.erase(curr_floor_req); //removing current floor's requests
 			passengers--;
 			curr_floor_req = std::find(requests.begin(), requests.end(), current_floor);
 		}

 		std::string dir;
 		if (direction == UP)
 		{
 			dir = "UP";
 		}
 		else
 		{		
 			dir = "DOWN";
 		}

 		//Entering requests for current floor
 		std::cout << "\n=======================================================\n"
    		"The current floor is " << current_floor 
    		<< " and number of people in the elevator is " << passengers 
    		<< "\n\nDirection of elevator is " << dir 
    		<< " and Total capacity of the elevator is " << capacity
    		<< "\n\nMinimum floor number is " << min_floor
    		<< " and Maximum floor number is " << max_floor
    		<< "\n\n=======================================================\n";

 		if (current_floor == max_floor)
 		{
 			direction = DOWN;
 		}
		else if (current_floor == min_floor) 		
		{
 			direction = UP;
 		}

 		set_request();
 		std::sort(requests.begin(), requests.end());	
 	}
}	

int main()
{
	std::string capacity_str, min_floor_num_str, max_floor_num_str;
	int min_floor_num, max_floor_num;
	std::size_t capacity;

	std::cout << "Enter minimum floor number, maximum floor number in the building\n";
	std::cin >> min_floor_num_str;
	std::cin >> max_floor_num_str;

	min_floor_num = stoi(min_floor_num_str);
	max_floor_num = stoi(max_floor_num_str);

	std::cout << "Enter capacity for the elevator\n";
	std::cin >> capacity_str;
	std::stringstream capacity_stream(capacity_str);
	capacity_stream >> capacity;

	Elevator elevator(min_floor_num, max_floor_num, capacity);
	elevator.start_elevator();	
}
