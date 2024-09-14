#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
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

  const string distance_warning = "Start point must be not equal end point";
  const string number_warning = "Number of roots must be more than 2";

  string get_min_max_str(const vector<double> &vec) {
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

  void vector_to_console(
      const vector<double> &vec) { // Writes all elements of vector to console
                                   // out vector_to_stream
    cout << vector_to_string(vec);
    cout << endl << get_min_max_str(vec) << endl;
  }

  void vector_to_file(const vector<double> &vec,
                      ofstream &file) { // Writes all elements of vector to file

    file << vector_to_string(vec);
    file << endl << get_min_max_str(vec);
    file.close();
  }

  void function_pushes(
      double numerator, double denominator,
      double x) { // Adds result of calculation to results collection,
                  // if the function doesn't exist in this point it
                  // adds this point to singularity collection

    if (denominator == 0) {
      throw invalid_argument("Division by zero");
    }

    function_values.push_back(numerator / denominator);
  }

  void vector_clear() { // Clears vectors
    function_values.clear();
    singularities.clear();
  }

  double calc_delta(const double &s_point, const double &e_point,
                    const int &N) {
    return (double)(e_point - s_point) / (N - 1);
  }

  bool check_distance(double s_point, double e_point) {
    return e_point != s_point;
  }

  bool check_root_count(double number) { return number > 2; }

  double init_delta(double s_point, double e_point) {

    int N;
    cout << "Please enter the number of roots" << endl;
    cin >> N;
    if (!check_root_count(N)) {
      cerr << number_warning << endl;
      init_delta(s_point, e_point);
    }
    delta = calc_delta(s_point, e_point, N);

    return delta;
  }

  void init() {

    cout << "Please enter Start and End points" << endl;
    cin >> start_point >> end_point;

    if (!check_distance(start_point, end_point)) {
      cerr << distance_warning << endl;
      init();
    }

    delta = init_delta(start_point, end_point);
  }

  void init(double s_point, double e_point, int N) {

    if (!check_distance(s_point, e_point)) {
      throw invalid_argument(distance_warning);
    }

    if (!check_root_count(N)) {
      throw invalid_argument(number_warning);
    }

    double dlt = calc_delta(s_point, e_point, N);

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

    double numerator = (pow(x, 2) - 5) * sqrt(abs(tan(x)));
    double denominator = x * exp(-2 * x);
    function_pushes(numerator, denominator, x);
  }

  void f_test2(double x) {
    double numerator = cos(2 * x) + pow(sin(x), 2) - 0.5;
    double denominator = 1;

    function_pushes(numerator, denominator, x);
  }

public:
  Madi() { init(); }

  Madi(double s_point, double e_point, int N) {
    try {
      init(s_point, e_point, N);

    } catch (const invalid_argument &e) {
      cerr << e.what() << endl;
      exit(1);
    }
  }

  ~Madi() { vector_clear(); };

  void f_range() {
    vector_clear();

    for (auto i = start_point; i <= end_point; i += delta) {
      try {
        f(i);
      } catch (invalid_argument) {
        singularities.push_back(i);
      }
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
