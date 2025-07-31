#include <bits/stdc++.h>
#include <fstream>
using namespace std;

class node{
    public:
        int id;    
        unordered_map<char, set<node*>> transitions;

        node(int n){
            id = n;
        }
};

int nodeId = 0;

// pair<node*,node*> -> represent a machine (initial idea)
// machine -> represents a finite automaton with a start and end node

class machine{
    public:
        node* start;
        node* end;

        machine(node* s, node* e){
            start = s;
            end = e;
        }
};

machine unitmachine(char symbol){
    node* start = new node(nodeId++);
    node* end = new node(nodeId++);
    start->transitions[symbol].insert(end);
    return {start,end};
}

machine unionMachine(machine machine1, machine machine2){
    node* start = new node(nodeId++);
    node* end = new node(nodeId++);
    
    start->transitions['@'].insert(machine1.start);
    start->transitions['@'].insert(machine2.start);
    machine1.end->transitions['@'].insert(end);
    machine2.end->transitions['@'].insert(end);
    return {start,end};
}

machine concatMachine(machine machine1, machine machine2){
    machine1.end->transitions['@'].insert(machine2.start);
    return {machine1.start, machine2.end};
}

machine kleeneMachine(machine machine1){
    node* start = new node(nodeId++);
    node* end = new node(nodeId++);
    
    start->transitions['@'].insert(machine1.start);
    start->transitions['@'].insert(end);
    machine1.end->transitions['@'].insert(end);
    machine1.end->transitions['@'].insert(machine1.start);
    return {start,end};
}

machine buildMachine(string postfix){
    stack<machine> machines;

    for (char c : postfix) {
        if (isalnum(c)) {
            machines.push(unitmachine(c));
        } 
        else if (c == '+') {
            machine m2 = machines.top(); 
            machines.pop();
            machine m1 = machines.top(); 
            machines.pop();
            machines.push(unionMachine(m1, m2));
        } 
        else if (c == '.') {
            machine m2 = machines.top(); 
            machines.pop();
            machine m1 = machines.top(); 
            machines.pop();
            machines.push(concatMachine(m1, m2));
        } 
        else if (c == '*') {
            machine m1 = machines.top(); 
            machines.pop();
            machines.push(kleeneMachine(m1));
        }
    }
    return machines.top();
}

bool isValidRegex(string regex) { //to be improved more
    int balance = 0;
    for (int i=0; i<regex.size(); i++) {
        if (
            !isalnum(regex[i]) && 
            regex[i] != '(' && 
            regex[i] != ')' && 
            regex[i] != '*' && 
            regex[i] != '+' && 
            regex[i] != '.')
        {
            return false; // Invalid character
        }

        char c = regex[i];
        if (c == '(') balance++;
        else if (c == ')') balance--;
        if (balance < 0) return false; 

        if(c=='+' || c=='.') {
            if (i==0 || i==regex.size()-1) return false;
            if (regex[i-1]=='(' || regex[i+1]==')') return false;
        }
    }
    return balance==0; 
}

string toPostFix(string regex) {        //done to eliminate the use of brackets
    stack<char> operators;
    unordered_map<char, int> precedenceMap = {
        {'+', 1},
        {'.', 2},
        {'*', 3}
    };
    string postfix = "";

    for (char c : regex) {
        if (isalnum(c)) postfix += c;
        else if (c == '(') operators.push(c);
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();
        } else {
            while (!operators.empty() && precedenceMap[operators.top()] >= precedenceMap[c]) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }
    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }
    return postfix;
}

void printNFA(machine nfa) {
    unordered_set<int> visited;
    queue<node*> q;
    q.push(nfa.start);

    cout << "\n --NFA Transition Table--" << endl;
    cout << "Start State: " << nfa.start->id << endl;
    cout << "Accept State: " << nfa.end->id << endl << endl;

    while (!q.empty()) {
        node* current = q.front();
        q.pop();

        if (visited.count(current->id)) continue;
        visited.insert(current->id);

        for (auto transition : current->transitions) {
            char symbol = transition.first;
            for (node* target: transition.second) {
                cout << current->id << " --" 
                     << (symbol == '@' ? "&" : string(1, symbol)) 
                     << "--> " << target->id << endl;
                q.push(target);
            }
        }
    }
}

void generateMermaidDiagram(machine nfa, string& filename) {
    ofstream fout(filename);
    fout << "flowchart LR" << endl;

    unordered_set<int> visited;
    queue<node*> q;
    q.push(nfa.start);

    while (!q.empty()) {
        node* current = q.front();
        q.pop();

        if (visited.count(current->id)) continue;
        visited.insert(current->id);

        for (auto transition : current->transitions) {
            char symbol = transition.first;
            for (node* target: transition.second) {
                fout << "    " << current->id << "((\"" << current->id << "\"))"
                     << " -- " << (symbol == '@' ? "ε" : string(1, symbol))
                     << " --> " << target->id << "((\"" << target->id << "\"))" << endl;
                q.push(target);
            }
        }
    }

    fout << "    style " << nfa.start->id << " fill:#aaf,stroke:#000,stroke-width:2px" << endl;
    fout << "    style " << nfa.end->id << " fill:#afa,stroke:#000,stroke-width:2px" << endl;
    fout.close();
}


int main(){
    string regex;
    cout << "Enter a regular expression: ";
    cin >> regex;

    if (!isValidRegex(regex)) {
        cout << "Wrong regex expression" << endl;
        return 0;
    }

    string postfix = "";
    postfix = toPostFix(regex);
    cout << "Postfix expression: " << postfix << endl;

    machine nfa = buildMachine(postfix);

    printNFA(nfa);
    string filename = "nfa_diagram.mmd";
    generateMermaidDiagram(nfa, filename);
}
