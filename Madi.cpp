#include "iostream"
#include "vector"
#include <cmath>
#include <fstream>

using namespace std;

class Madi {

private:
  vector<double> crit_points;
  vector<double> singularities;

  double start_point, end_point, delta;

private:
  void function_pushes(double numerator, double denominator, int x) {
    if (denominator == 0) {
      singularities.push_back(x);
      return;
    }
    crit_points.push_back(numerator / denominator);
  }

  void vector_clear() {
    crit_points.clear();
    singularities.clear();
  }

  void vector_to_stream(vector<double> vec) {
    for (const auto &item : vec) {
      cout << item << " ";
    }
    cout << endl;
  }

  void vector_to_file(vector<double> vec, ofstream &file) {
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
    return fabs((s_point + delta) - round(s_point + delta)) < 1e-9;
  }

  double Init_Delta(double s_point, double e_point) {
    int N;
    double delta;

    while (true) {
      cout << "Please Enter number of roots" << endl;
      cin >> N;
      delta = delta_calc(s_point, e_point, N);

      if (num_roots_checker(s_point, delta)) {
        break;
      }

      cout << "Number of roots is incorrect" << endl;
    }

    return delta;
  }

  void Init() {
    double s_point, e_point;

    cout << "Please enter Start and End points" << endl;
    cin >> s_point >> e_point;

    if (!dist_checker(s_point, e_point)) {
      cout << "Distance between two points must be more than 2";
      Init();
    }
    delta = Init_Delta(s_point, e_point);
  }

  void Init(double s_point, double e_point, int N) {
    if (!dist_checker(s_point, e_point)) {
      cout << "Distance between two points must be more than 2";
      return;
    }

    double dlt = delta_calc(s_point, e_point, N);

    if (!num_roots_checker(s_point, N)) {
      cout << "Number of roots is incorrect" << endl;
      return;
    }

    start_point = s_point;
    end_point = e_point;
    delta = dlt;
  }

  void f_test(int x) {
    vector_clear();

    double numerator = 25 * pow(x, 2);
    double denominator = x;

    function_pushes(numerator, denominator, x);
  }

  void f(int x) {
    vector_clear();

    double numerator = sin(pow(x / 2, 2)) + 23 * x;
    double denominator = cos(x / 2);

    function_pushes(numerator, denominator, x);
  }

public:
  Madi() { Init(); }
  Madi(double s_point, double e_point, int N) { Init(s_point, e_point, N); }

  void f_range() {
    for (auto i = start_point + delta; i < end_point; i += delta) {
      f_test(i);
    }
  }

  void print(bool console = true) {
    if (console) {
      cout << "Critical points:" << endl;
      vector_to_stream(crit_points);

      cout << "Singularity points" << endl;
      vector_to_stream(singularities);

    } else {
      ofstream crit_output_file("./crit_points.txt");
      ofstream sing_output_file("./singularity.txt");

      vector_to_file(crit_points, crit_output_file);
      vector_to_file(singularities, sing_output_file);
    }
    vector_clear();
  }
};
