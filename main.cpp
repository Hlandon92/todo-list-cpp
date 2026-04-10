//
//  main.cpp
//  Project 1
//
//  Created by landon hillborn on 4/08/26.
//  description: Task manager, allowes adding, deleting, and changing statuses of tasks

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Task {
    string title;
    string status; //Pending, In progress, Done
    string deadline; // e.g. 2026-04-15
};

vector<Task> tasks;

// Load tasks
void loadTasks() {
    ifstream file("/Users/mrworldwide/Library/Mobile Documents/com~apple~TextEdit/Documents/tasks.txt");
    Task t;
    while (getline(file, t.title))
    {
        getline(file, t.status);
        getline(file, t.deadline);
        tasks.push_back(t);
    }
    file.close();
}
// Save tasks
void saveTasks() {
    ofstream file("/Users/mrworldwide/Library/Mobile Documents/com~apple~TextEdit/Documents/tasks.txt");
    for (const Task& t: tasks)
    {
        file << t.title << endl;
        file << t.status << endl;
        file << t.deadline << endl;
    }
    file.close();
}

// View tasks
void viewTasks() {
    if (tasks.empty())
    {
        cout << "No tasks available.\n";
        return;
    }
    
    cout << "\n    TASK LIST   \n";
    for (int i = 0; i < tasks.size(); i++)
    {
        cout << i + 1 << ". " << tasks[i].title << endl;
        cout << "   Status: " << tasks[i].status << endl;
        cout << "   Deadline: " << tasks[i].deadline << endl;
    }
}

// Add task
void addTask() {
    Task t;
    cin.ignore();
    
    cout << "Enter task: ";
    getline(cin, t.title);
    
    cout << "Enter deadline (YYYY-MM-DD): ";
    getline(cin, t.deadline);
    
    t.status = "Pending";
    tasks.push_back(t);
    
    cout << "Task added!\n";
}

// Update status
void updateStatus() {
    int index;
    int choice;
    
    if (tasks.empty())
    {
        cout << "No tasks found.\n";
        return;
    }
    else
    {
        viewTasks();
        
        cout << "select task number: ";
        cin >> index;
        
        if (index < 1 || index > tasks.size())
        {
            cout << "Invalid selection.\n";
            return;
        }
        
        cout << "1. Pending\n2. In Progress\n3. Done\nChoose status: ";
        cin >> choice;
        
        switch (choice)
        {
            case 1: tasks[index - 1].status = "Pending"; break;
            case 2: tasks[index - 1].status = "In Progress"; break;
            case 3: tasks[index - 1].status = "Done"; break;
            default:
                cout << "Invalid choice.\n";
                return;
        }
        
        cout << "Status updated!\n";
    }
}

    // Delete task
void deleteTask() {
    int index;
        
    if (tasks.empty())
    {
        cout << "No tasks found.\n";
        return;
    }
    else
    {
        viewTasks();
        
        cout << "Enter task number to delete: ";
        cin >> index;
        
        if (index < 1 || index > tasks.size())
        {
            cout << "Invalid task number.\n";
            return;
        }
        
        tasks.erase(tasks.begin() + index - 1);
        cout << "Task deleted!\n";
    }
}

void deleteAllTasks() {
    char confirm;
    
    if (tasks.empty())
    {
        cout << "No tasks found.\n";
        return;
    }
    else
    {
        viewTasks();
        
        cout << "Are you sure you want to delete ALL tasks? (y/n): ";
        cin >> confirm;
        
        while (true)
        {
            if (confirm == 'y' || confirm == 'Y')
            {
                tasks.clear();
                cout << "All tasks deleted!\n";
                break;
                return;
            }
            else if (confirm == 'n' || confirm == 'N')
            {
                cout << "Cancelled.";
                break;
                return;
            }
            else
            {
                cout << "Invalid input. (y/n): ";
                cin >> confirm;
            }
        }
    }
}

int main() {
    int choice;
    loadTasks();
    
    do {
        cout << "\n   T0-DO LIST   \n";
        cout << "1. view Tasks\n";
        cout << "2. Add Task\n";
        cout << "3. Update Task status\n";
        cout << "4. Delete Task\n";
        cout << "5. Delete ALL Tasks!\n";
        cout << "6. Exit\n";
        cout << "Choose: ";
        cin >> choice;
        
        switch (choice)
        {
            case 1: viewTasks(); break;
            case 2: addTask(); break;
            case 3: updateStatus(); break;
            case 4: deleteTask(); break;
            case 5: deleteAllTasks(); break;
            case 6: saveTasks();
                cout << "GoodBye!\n";
                break;
            default:
                cout << "Invalid option. (1-6)\n";
        }
    }  while (choice != 6);
    
    return 0;
}
