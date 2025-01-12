#include<iostream>

struct Node {
  int data;
  Node *next;
};

Node* NewNode(int x) {
  Node *node = new Node;
  node->data = x;
  node->next = NULL;
  return node;
}

struct Queue{
  Node *front;
  Node *rear;
};

void CreateQueue(Queue &q) {
  q.front = q.rear = NULL;
}

int Empty(Queue &q){
  if(q.front == NULL) {
    return 1;
  }
  return 0;
}

void EnQueue(Queue &q, Node* node) { //add
  if (Empty(q)){
    q.front = q.rear = node;
  }
  else{
    q.rear->next = node;
    q.rear = node;
  }
}

int DeQueue(Queue &q) { //remove
  if (Empty(q)) {
    return 0;
  }
  Node *node = q.front;
  int data = node->data;
  q.front = node->next;
  delete node;
  if (q.front == NULL) {
    q.rear = NULL;
  }
  return data;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
  unsigned int n;
  std::cin >> n;
  char operant;
  int x;
  Queue queueB;
  CreateQueue(queueB);
  Node *node;
      
  for(unsigned int i = 1; i <= n; i++){
    std::cin >> operant;
    if (operant == '+'){
        std::cin >> x;
      node = NewNode(x);
      EnQueue(queueB, node);
    }
    else if(operant == '-')
      std::cout << DeQueue(queueB) << "\n";
    }

    while(!Empty(queueB)){
      DeQueue(queueB);
    }
  return 0;
}
