#pragma once

#include <iostream>

/**
 * @brief A collection of output functions to shout information on the stdout/stderr.
 */
class Debug {
public:
  /**
   * @brief log The default log, it prints args on the stdout.
   * @param args The arguments to be printed on the terminal.
   */
  template<typename... Ts>
  static void log(const Ts&... args)
  {
      std::cout << "INFO: ";

      int expanded[] = { (std::cout << args << "", 0)... };
      (void)expanded;

      std::cout << std::endl;
  }

  /**
   * @brief log_warn The warning log, it prints out args on the stdout
   * which should be taken with care.
   * @param args The arguments to be printed on the terminal.
   */
  template<typename... Ts>
  static void log_warn(const Ts&... args)
  {
      std::cout << "WARN: ";

      int expanded[] = { (std::cout << args, 0)... };
      (void)expanded;

      std::cout << std::endl;
  }

  /**
   * @brief log_err The error log, use this to print really bad things that
   * happened with something.
   * @param args The arguments to be printed on the terminal.
   */
  template<typename... Ts>
  static void log_err(const Ts&... args)
  {
      std::cerr << "ERR : ";

      int expanded[] = { (std::cerr << args, 0)... };
      (void)expanded;

      std::cerr << std::endl;
  }
};
