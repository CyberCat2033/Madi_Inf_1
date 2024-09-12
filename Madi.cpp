#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Madi {

private:
  vector<double> function_values; // List of values of function
  vector<double>
      singularities; // List of X values for which function doesn't exist
  double start_point, end_point;
  double delta;
  const string distance_warning = "Start point must be != end point\n";

  const string number_warning = "Number of roots must be more than 2";

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

  string vector_to_string(const vector<double> &vec) {
    if (vec.size() < 1) {
      return "";
    } else {
      ostringstream result;
      for (const auto &item : vec) {
        result << item << " ";
      }
      result << endl;
      return result.str();
    }
  }

  void function_pushes(
      double numerator, double denominator,
      double x) { // Adds result of calculation to results collection,
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

  void vector_to_console(
      const vector<double> &vec) { // Writes all elements of vector to console
                                   // out vector_to_stream
    cout << vector_to_string(vec);
    cout << endl << vector_Min_Max(vec) << endl;
  }

  void vector_to_file(const vector<double> &vec,
                      ofstream &file) { // Writes all elements of vector to file

    file << vector_to_string(vec);
    file << endl << vector_Min_Max(vec);
    file.close();
  }

  double delta_calc(double s_point, double e_point, int N) {
    return (double)(e_point - s_point) / (N - 1);
  }

  bool dist_checker(double s_point, double e_point) {
    return e_point != s_point;
  }

  bool num_roots_checker(double delta) { return delta > 2; }

  double Init_Delta(double s_point, double e_point) {
    int N;
    cout << "Please enter the number of roots" << endl;
    cin >> N;
    delta = delta_calc(s_point, e_point, N);

    if (!num_roots_checker(delta)) {
      cout << number_warning << endl;
      Init_Delta(s_point, e_point);
    }

    return delta;
  }

  void Init() {

    cout << "Please enter Start and End points" << endl;
    cin >> start_point >> end_point;

    if (!dist_checker(start_point, end_point)) {
      cout << distance_warning << endl;
      Init();
    }

    delta = Init_Delta(start_point, end_point);
  }

  void Init(double s_point, double e_point, int N) {

    if (!dist_checker(s_point, e_point)) {
      cout << distance_warning << endl;
      exit(1);
    }

    double dlt = delta_calc(s_point, e_point, N);

    if (!num_roots_checker(N)) {
      cout << number_warning << endl;
      exit(1);
    }

    start_point = s_point;
    end_point = e_point;
    delta = dlt;
  }

  void f_test(double x) {

    double numerator = 25 * pow(x, 2);
    double denominator = x;

    function_pushes(numerator, denominator, x);
  }

  void f(double x) {

    double numerator = sin(pow(x / 2, 2)) + 23 * x;
    double denominator = cos(x / 2);

    function_pushes(numerator, denominator, x);
  }

  void f_test2(double x) {
    double numerator = cos(2 * x) + pow(sin(x), 2) - 0.5;
    double denominator = 1;

    function_pushes(numerator, denominator, x);
  }

public:
  Madi() { Init(); }
  Madi(double s_point, double e_point, int N) { Init(s_point, e_point, N); }

  void f_range() {
    vector_clear();

    for (auto i = start_point; i <= end_point; i += delta) {
      f_test(i);
    }
  }

  void print(bool console = true) {
    if (console) {
      cout << endl << "Function values:" << endl;
      vector_to_console(function_values);

      cout << "Singularity points:" << endl;
      vector_to_console(singularities);

    } else {

      ofstream crit_output_file("./function_values.txt");
      ofstream sing_output_file("./singularity.txt");

      vector_to_file(function_values, crit_output_file);
      vector_to_file(singularities, sing_output_file);
    }
  }
};
