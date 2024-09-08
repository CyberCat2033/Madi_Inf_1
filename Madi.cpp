#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Madi {

private:
  vector<double> function_values; // List of values of function
  vector<double>
      singularities; // List of X values for which function doesn't exist
  int start_point, end_point;
  double delta;

  string vector_Min_Max(const vector<double> &vec) {
    if (vec.size() < 2) {
      return "";
    } else {
      ostringstream result;
      result << "Max point = " << *max_element(vec.begin(), vec.end()) << endl;
      result << "Min point = " << *min_element(vec.begin(), vec.end()) << endl;
      return result.str();
    }
  }

  void
  function_pushes(double numerator, double denominator,
                  int x) { // Adds result of calculation to results collection,
                           // if the function doesn't exist in this point it
                           // adds this point to singularity collection

    if (denominator == 0) {
      singularities.push_back(x);
      return;
    }
    function_values.push_back(numerator / denominator);
  }

  void vector_clear() { // Clears vectors
    function_values.clear();
    singularities.clear();
  }

  void vector_to_stream(
      const vector<double>
          &vec) { // Writes all elements of vector to console out stream

    for (const auto &item : vec) {
      cout << item << " ";
    }
    cout << endl;
    cout << vector_Min_Max(vec) << endl;
  }

  void vector_to_file(const vector<double> &vec,
                      ofstream &file) { // Writes all elements of vector to file

    for (const auto &item : vec) {
      file << item << " ";
    }
    file << endl << vector_Min_Max(vec);
    file.close();
  }

  double delta_calc(int s_point, int e_point, int N) {
    return (double)(e_point - s_point) / (N - 1);
  }

  bool dist_checker(int s_point, int e_point) { return e_point - s_point > 3; }

  bool num_roots_checker(int s_point, double delta) {
    return (int)(s_point + delta) == (s_point + delta);
  }

  double Init_Delta(double s_point, double e_point) {
    int N;
    cout << "Please Enter number of roots" << endl;
    cin >> N;
    delta = delta_calc(s_point, e_point, N);

    if (!num_roots_checker(s_point, delta)) {
      cout << "Number of roots is incorrect" << endl;
      Init_Delta(s_point, e_point);
    }

    return delta;
  }

  void Init() {

    cout << "Please enter Start and End points" << endl;
    cin >> start_point >> end_point;

    if (!dist_checker(start_point, end_point)) {
      cout << "Distance between two points must be more than 2" << endl;
      Init();
    }

    delta = Init_Delta(start_point, end_point);
  }

  void Init(int s_point, int e_point, int N) {

    if (!dist_checker(s_point, e_point)) {
      cout << "Distance between two points must be more than 2" << endl;
      return;
    }

    double dlt = delta_calc(s_point, e_point, N);

    if (!num_roots_checker(s_point, N)) {
      cout << "Number of roots in incorrect" << endl;
      return;
    }

    start_point = s_point;
    end_point = e_point;
    delta = dlt;
  }

  void f_test(int x) {

    double numerator = 25 * pow(x, 2);
    double denominator = x;

    function_pushes(numerator, denominator, x);
  }

  void f(int x) {

    double numerator = sin(pow(x / 2, 2)) + 23 * x;
    double denominator = cos(x / 2);

    function_pushes(numerator, denominator, x);
  }

public:
  Madi() { Init(); }
  Madi(int s_point, int e_point, int N) { Init(s_point, e_point, N); }

  void f_range() {
    vector_clear();

    for (auto i = start_point; i <= end_point; i += delta) {
      f_test(i);
    }
  }

  void print(bool console = true) {
    if (console) {
      cout << endl << "Critical points:" << endl;
      vector_to_stream(function_values);

      cout << "Singularity points:" << endl;
      vector_to_stream(singularities);

    } else {

      ofstream crit_output_file("./crit_points.txt");
      ofstream sing_output_file("./singularity.txt");

      vector_to_file(function_values, crit_output_file);
      vector_to_file(singularities, sing_output_file);
    }
  }
};
