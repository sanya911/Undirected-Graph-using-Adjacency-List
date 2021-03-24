
#include <stdio.h>
#include <iostream>
using namespace std;
//Node for BST
struct Node
{
    int data;
    struct Node* next;
};

//Linkedlist to store each Vertices
struct LList{
    struct Node* head;
};

class adjList{
    int SIZE;
    struct LList *A;
    int *visited;
    int *queue;
    int front = 0;
    int rear = 0;
    
    public:
            adjList(int SIZE){
                this->SIZE = SIZE;
                cout<<SIZE<<"\n";
                A = new LList [SIZE+2];
                visited = new int [SIZE+2];
                queue = new int [SIZE+2];
                for(int i = 0;i<SIZE;i++){
                    visited[i] = 0;
                    A[i].head = NULL;
                }
            }
            
            //To connect edge
            void addEdge(int n1, int n2){
                if(n1>SIZE or n1<1 or n2>SIZE or n2<1){
                    cout<<"Node does not exist!";
                    return;
                }
                if(n1==n2){
                    struct Node * newNode1 = new Node;
                    newNode1->data = n2;
                    newNode1->next = A[n1-1].head;
                    A[n1-1].head = newNode1;
                    return;
                }
                struct Node * newNode1 = new Node;
                struct Node * newNode2 = new Node;
                newNode1->data = n2;
                newNode1->next = A[n1-1].head;
                A[n1-1].head = newNode1;
                newNode2->data = n1;
                newNode2->next = A[n2-1].head;
                A[n2-1].head = newNode2;
                
            }
            //To display 
            void display(){
                struct Node *ptr;
                for(int i =0;i<SIZE;i++){
                    ptr = A[i].head;
//                    cout<<i+1<<" is connected to ";
                    while(ptr != NULL){
                        cout<<ptr->data<<" ";
                        ptr = ptr->next;
                    }
                    cout<<"\n";
                }
            }
            
            //To Search 
            void displayNode(int data){
                struct Node *ptr;
                cout<<"Node are\n";
                ptr = A[data-1].head;
                while(ptr != NULL){
                    cout<<ptr->data<<" ";
                    ptr = ptr->next;
                }
                cout<<"\n";
            }
            //To add node
            void addNode(){
                A[SIZE].head = NULL;
                SIZE = SIZE+1;
                cout<<"\nNew Node is added\n";
            }
            
            //To delete node
            void deleteNode(int data){
                struct Node *ptr;
                int i = 0;
                int flag = 0;
                while(i<SIZE){
                    if(data-1 == i and flag == 0){
                        cout<<"data row "<<data-1<<"\n";
                        for(int j = i;j<SIZE-1;j++){
                            A[j].head = A[j+1].head; 
                        }
                        SIZE = SIZE-1;
                        flag = 1;
                        i = i;
                        continue;
                    }
                    else if(A[i].head != NULL and A[i].head->data == data){
                        if(A[i].head->next == NULL){
                            A[i].head = NULL;
                        }
                        else{
                            A[i].head->data = A[i].head->next->data;  
                            ptr = A[i].head->next;
                            A[i].head->next = A[i].head->next->next;
                            // free(ptr);
                        }
                        i = i+1;
                        continue;
                    }
                    
                    else{
                        if(A[i].head == NULL){
                            i = i+1;
                            continue;
                        }
                        ptr = A[i].head;
                        while(ptr->next != NULL and ptr->next->data != data){
                            ptr = ptr->next;
                        }

                        if(ptr->next == NULL){
                            i = i+1;
                            continue;
                        }
                        ptr->next = ptr->next->next;
                        i = i+1;
                        continue;
                    }
                    i = i+1;
                }
            }
            //To intialize all visited node = 0
            void DFS_visited(int data){
                visited = new int[SIZE];
                for(int i = 0; i<SIZE; i++){
                    visited[i] = 0;
                }
                DFS(data);
            }

            void DFS(int data){
                cout<<"-->"<<data<<"     ";
                visited[data-1] = 1;
                struct Node *ptr;
                ptr = A[data-1].head;
                while(ptr != NULL){
                    if(visited[(ptr->data)-1]==0){
                        DFS(ptr->data);
                    }
                    ptr = ptr->next;
                }

            }
            
            void enqueue(int data){
                queue[rear] = data;
                rear = rear+1;
            }
        
            void dequeue(){
                if(front == rear){
                    return;
                }
                else{
                    for(int i =0;i<SIZE;i++){
                        queue[i] = queue[i+1];
                    }
                    rear = rear-1;
                }
            }

            void BFS(int data){
                for(int i =0; i<SIZE;i++){
                    visited[i] = 0;
                }
                visited[data-1] = 1;
                enqueue(data);
                struct Node *ptr;
                while(front != rear){
                    ptr = A[queue[front]-1].head;
                    while(ptr != NULL){
                        if(visited[(ptr->data)-1] == 0){
                            visited[(ptr->data)-1] = 1;
                            enqueue(ptr->data);
                        }
                        ptr = ptr->next;
                    }
                    cout<<"-->"<<queue[front]<<"    ";
                    dequeue();
                }
            }
};

int main()
{
    int v, e;
    int search;
    int choice;
    int n1, n2;
    cout<<"No. of vertices: ";
    cin>>v;
    adjList graph(v);
    cout<<"Total no. of edges: ";
    cin>>e;
    for(int i = 0;i<e;i++){
        cout<<"\n  first node: ";
        cin>>n1;
        cout<<" \nsecond node: ";
        cin>>n2;
        graph.addEdge(n1,n2);
    }
    while(1)
	{
        cout<<"\n";
		cout<<"1.Search\n";
		cout<<"2.Insert Node\n";
		cout<<"3.Insert Edge\n";
		cout<<"4.Delete\n";
		cout<<"5.DFS\n";
		cout<<"6.BFS\n";
		cout<<"7.Display\n";
		cout<<"8.Quit\n";
	    cout<<"Enter your choice : ";
		cin>>choice;

		switch(choice)
		{
    		case 1:
                cout<<"Enter the node to be searched: ";
                cin>>search;
                graph.displayNode(search);
    			break;
    		case 2:
    		    graph.addNode();
    			break;
    		case 3:
    		    cout<<"Enter the first node that you want to connect  :";
                cin>>n1;
                cout<<"Enter the second node : ";
                cin>>n2;
                graph.addEdge(n1, n2);
                break;
    		case 4:
    		    cout<<"Enter the node to be deleted: ";
    		    cin>>search;
                graph.deleteNode(search);
    		    break;
    		case 5:
    		    graph.DFS_visited(1);
    		    break;
    		case 6: 
    		    graph.BFS(1);
    		    break;
    		case 7:
    		    graph.display();
    		    break;
            case 8:
    		    exit(1);
    		default:
    			printf("Wrong choice\n");
		}/*End of switch */
	}/*End of while */

    return 0;
}


