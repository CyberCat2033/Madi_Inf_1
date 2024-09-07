#include "iostream"
#include "vector"
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

class Madi {

private:
  vector<double> function_values; // List of values of function
  vector<double>
      singularities; // List of X values for which function doesn't exist

  double start_point, end_point, delta;

private:
  void function_pushes(double numerator, double denominator, int x) {

    if (denominator == 0) {
      singularities.push_back(x);
      return;
    }
    function_values.push_back(numerator / denominator);
  }

  void vector_clear() {
    function_values.clear();
    singularities.clear();
  }

  void vector_to_stream(const vector<double> &vec) {

    for (const auto &item : vec) {
      cout << item << " ";
    }

    cout << "\n" << endl;
  }

  void vector_to_file(const vector<double> &vec, ofstream &file) {

    for (const auto &item : vec) {
      file << item << " ";
    }
    file.close();
  }

  double delta_calc(double s_point, double e_point, int N) {
    return (e_point - s_point) / (N - 1);
  }

  bool dist_checker(double s_point, double e_point) {
    return e_point - s_point > 3;
  }

  bool num_roots_checker(double s_point, double delta) {
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

  void Init(double s_point, double e_point, int N) {

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
  Madi(double s_point, double e_point, int N) { Init(s_point, e_point, N); }

  void f_range() {
    vector_clear();

    for (auto i = start_point; i <= end_point; i += delta) {
      f_test(i);
    }
  }

  void print(bool console = true) {
    if (console) {
      cout << "Critical points:" << endl;
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
