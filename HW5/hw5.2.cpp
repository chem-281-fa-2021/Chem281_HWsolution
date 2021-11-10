#include "queue.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;
#include <map>

class hw5_2{
  private:
    Queue* alljobs;
    unsigned int num_jobs;
    map<unsigned int, unsigned int> num_dependency;
    Queue* jobseq;

  public:
    hw5_2(char* fname);
    ~hw5_2(){
      delete[] alljobs;
    }
    void print();
    int okjob();
    void update(unsigned int ijob);
    int solve();
    Queue* getanswer(){return jobseq;}
};

hw5_2::hw5_2(char* fname){
  num_jobs = 0;
  ifstream in(fname, ios::in);
  string line;
  getline(in, line);
  istringstream iss(line);
  if (!(iss >> num_jobs))
    throw invalid_argument("There is some problem with input format.");

  alljobs = new Queue[num_jobs];
  jobseq = new Queue;
  for (size_t k = 0; k < num_jobs; k++){
    num_dependency[k] = 0;
  }
  while (getline(in, line))
  {
    istringstream iss(line);
    unsigned int i_job, i_dependent;
    if (!(iss >> i_job >> i_dependent))
      throw invalid_argument("There is some problem with input format.");
    
    alljobs[i_dependent].insert(i_job);
    num_dependency[i_job] ++;
  }
}

void hw5_2::print(){
  for (size_t k = 0; k < num_jobs; k++){
    cout << k << endl;
    alljobs[k].printall();
    cout << endl;
  }
    cout << "num dependency"<<endl;
  for (auto& p :num_dependency){
    cout << p.first << ": " << p.second<<endl;
  }
}

int hw5_2::okjob(){
  if(num_dependency.empty())
    return -1;
  int target = -2;
  for(auto it = num_dependency.begin(); it != num_dependency.end(); it++) {
      if(it->second == 0){
        target = it->first;
        num_dependency.erase(it);
        return target;
      }
  }
  return target;
}

void hw5_2::update(unsigned int ijob){
  while (!alljobs[ijob].checkempty())
  {
    unsigned int dependency = alljobs[ijob].remove();
    num_dependency[dependency] --;
  }
}

int hw5_2::solve(){
  int jobtarget = okjob();
  while (jobtarget >= 0)
  {
    update(jobtarget);
    nodedata ijob = jobtarget;
    jobseq->insert(ijob);
    jobtarget = okjob();
  }
  if (jobtarget == -2)
    throw invalid_argument("There might be chain dependency.");
  return 0;
}



int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("usage: ./hw5.2 input file\n");
    return EXIT_FAILURE;
  }
  try
  {
    char* filename = argv[1];
    hw5_2 problem(filename);
    problem.solve();
    Queue* answer = problem.getanswer();
    answer->printall();    
  }
  catch (std::runtime_error &e)
  {
    cout << e.what() << "\n";
  }

  return EXIT_SUCCESS;
}
