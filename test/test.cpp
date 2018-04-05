// scope_guard c++11 test
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
// Copyright (c) 2018 Daniil Goncharov <neargye@gmail.com>.
//
// Permission is hereby  granted, free of charge, to any  person obtaining a copy
// of this software and associated  documentation files (the "Software"), to deal
// in the Software  without restriction, including without  limitation the rights
// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <scope_guard.hpp>

TEST_CASE("DEFER") {
  SECTION("int") {
    int i = 0;
    {
      REQUIRE(i == 0);
      DEFER{
        i = 2;
      };
      i = 1;
      REQUIRE(i == 1);
    }
    REQUIRE(i == 2);
  }

  SECTION("ofstream") {
    std::ofstream file;
    {
      file.open("test.txt", std::fstream::out | std::ofstream::trunc);
      REQUIRE(file.is_open());
      DEFER{
        file << "close file" << std::endl;
        file.close();
      };
      REQUIRE(file.is_open());
      file << "write to file" << std::endl;
    }
    REQUIRE(!file.is_open());
  }
}
