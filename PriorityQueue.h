/*
 * C++ Program to Implement Priority Queue
 */
#ifndef __priorityqueue
#define __priorityqueue
#include <iostream>
using namespace std;

/*
 * Node Declaration
 */
template<class T>
struct node
{
    int priority;
    T info;
    struct node<T>* link;
};
/*
 * Class Priority Queue
 */
template<class T>
class PriorityQueue
{
private:
    node<T>* front;
public:
    PriorityQueue()
    {

        front = NULL;
    }
    /*
     * Insert into Priority Queue
     */
    bool IsEmpty()
    {

        return (front == NULL);
    }
    void Enqueue(T item, int priority)
    {
        node<T>* tmp, * q;
        tmp = new node<T>;
        tmp->info = item;
        tmp->priority = priority;
        if (front == NULL || priority > front->priority)
        {
            tmp->link = front;
            front = tmp;
        }
        else
        {
            q = front;
            while (q->link != NULL && q->link->priority >= priority)
                q = q->link;
            tmp->link = q->link;
            q->link = tmp;
        }
    }
    /*
     * Delete from Priority Queue
     */
    bool Dequeue(T& ele)
    {
        node<T>* tmp;
        if (front == NULL)
            return false;
        else
        {
            tmp = front;
            ele = front->info;
            front = front->link;
            return ele;
        }
    }
    /*
     * Print Priority Queue
     */
   

    int get_count() {
        node<T>*temp = front; // here
        int c = 0;
        while (temp)
        {
            c++;
            temp = temp->link;
        }
        return c;
    }
    bool peek(T& ele)
    {
        if (IsEmpty()) return false;
        ele = front->info;
        return true;

    }
};
#endif