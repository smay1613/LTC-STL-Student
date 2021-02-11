## Workflow
1. __Fork__ the repo
2. __Clone__ forked version
3. __Create branch__ (from master!) with task number and descriptive name _(see [rule #3](https://github.com/smay1613/LTC-STL-Student#3-pull-request-name-should-contain-task-name-and-your-surname-eg-iterators-task-1---woodman))_
4. __Implement__ your task
5. __Check__ if your work doesn't go against the rules
6. __Commit__ changes and __push branch__ to a remote
7. __Create pull request__ [IN THIS REPO](https://github.com/smay1613/LTC-STL-Student) from your branch
8. __Check__ your pull request
9. __Wait__ until review is done
10. __Check__ results and __answer__ questions 
  
  
## Check list:
- [x] All tests are passed
- [x] Branch is correct and branched from master
- [x] Pull request changes are correct (only code from one task)
- [x] Pull request title contains task name and your surname
  
  
## Rules

### 1. If pull request contain any non-related changes, it will be rejected without review.
### 2. If tests are not passed, pull request will be rejected
### 3. Pull request title should contain task name and your surname _(e.g iterators task (1) - Petrov)_
### 4. Don't modify tests
### 5. Don't change task interface
  
  
## Project structure
__Please respect the template:__
```shell
├───include              # Your task is defined here.                                                                                                          
├───src                  # !!!!! Your implementation will be here (for non-template tasks) !!!!!                                                                
└───tests                                                                        
    ├───cmake_modules    # Utils for downloading unit tests                                                                                                    
    └───unit_tests                                                                                                              
        ├───headers      # Mock classes and testing data
        └───src          # !!!!! Task unit tests !!!!!
```
  
  
## Troubleshooting
If something does not work, check [recommended environment](https://github.com/smay1613/LTC-STL-Student#recommended-environment).
If google test does not compile, try define in CMake:
`gtest_disable_pthreads=ON`
  
  
## Requirements
**Tools:**  
  * **CMake 3.0+**
  * **C++ compiler that supports C++17 filesystem** (**gcc** recommended, because code tested only for it)
  * **Git**
  
  
For Windows:  
_[cmake](https://cmake.org/download/)_  
_[Qt Creator + compiler](https://www.qt.io/download-qt-installer)_  
_[Git](https://git-scm.com/downloads)_
  
For Ubuntu:  
_`sudo apt-get install cmake qtcreator git gcc`_  
  
  
## Recommended environment
* Ubuntu  
* Qt Creator IDE  
* gcc 7.3.0+ (or latest)  
* gdb  

## Best practices and codestyle  
If you want to improve your code style during the training, **please follow C++ Core Guidelines**.
Especially, you must follow these rules:
* https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-naming (MAKE YOUR CODE READABLE AS ENGLISH - AVOID ABBREVIATIONS AND MAGIC NUMBERS/VARIABLES!)
* https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rcpl-C (USE C++, NOT C!)
* https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-resource (DON'T MANUALLY CONTROL THE RESOURCES!)
* https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-performance (DON'T OPTIMIZE JUST BECAUSE YOU WANT!)
* https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-expr (DON'T REINVENT THE WHEEL AND MAKE CODE SIMPLER TO UNDERSTAND!)


## If you are not familiar with git:
1. [Install git](https://git-scm.com/downloads)
2. [Setup ssh access](https://docs.github.com/en/github/authenticating-to-github/connecting-to-github-with-ssh)
2. Learn how to:
   * _Clone repository_:  
        `git clone git@github.com:smay1613/LTC-STL-Student.git` (with your fork!)
   * _Check current status (branch, remote, etc) - do this before and after any command!_:  
        `git status`
   * _Switch to another branch_:  
        `git checkout -b task_name_YourSurname` (-b creates a branch from the current branch)
   * _....implement task....._
   * _....check if everything is ok...._
   * _Add files to index:_   
        `git add *changed files with code*`
   * _Commit changes and write __meaningful__ commit message:_  
        `git commit`
   * _Push to remote:_  
        `git push`
   * _....create pull request on [Github](https://github.com/smay1613/LTC-STL-Student/pulls)...._
   * _Switch back to master branch:_  
        `git checkout master`

## How to sync a fork
1. https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/configuring-a-remote-for-a-fork
2. https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/syncing-a-fork

## Help wanted!
If you want to get some experience, you can contribute to this repository:
* Add more tests for practice
* Improve CMake
* If you have bash experience, you can help with repository automation (for pull requests) using Github Actions API:
  * Build
  * Testing
  * Labeling
  * Mark counter
