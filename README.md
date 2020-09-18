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
  
  
## To check list:
- [x] Run all tests when implementation is ready
- [x] Check if branch is correct and branched from master
- [x] Check pull request changes
- [x] Check pull request title
  
  
## Rules

### 1. If pull request contain any non-related changes, it will be rejected without review.
### 2. If tests are not passed, pull request will be rejected
### 3. Pull request name should contain task name and your surname _(e.g iterators task (1) - Woodman)_
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
1. **Packages:**  
     * **unzip**
      * **wget**  
2. **Tools:**  
     * **CMake 3.0+**
     * **C++ compiler that supports C++17 filesystem**
  
  
For Windows:  
_[unzip](http://gnuwin32.sourceforge.net/packages/unzip.htm)   
[wget](http://gnuwin32.sourceforge.net/packages/wget.htm)  
[cmake](https://cmake.org/download/)_    
  
For Ubuntu:  
_`sudo apt-get install wget unzip cmake`_  
  
  
## Recommended environment
* Ubuntu  
* Qt Creator IDE  
* gcc 7.3.0+ (or latest)  
* gdb  

## If you are not familiar with git:
1. [Install git](https://git-scm.com/downloads)
2. [Setup ssh access](https://docs.github.com/en/github/authenticating-to-github/connecting-to-github-with-ssh)
2. Learn how to:
   * _Clone repository_:  
        `git clone git@github.com:smay1613/LTC-STL-Student.git`
   * _Check current status (branch, remote, etc) - do this before and after any command!_:  
        `git status`
   * _Switch to another branch_:  
        `git checkout -b task_name_YourSurname` (-b creates a branch from the current branch)
   * _....implement task....._
   * _....check if everything is ok...._
   * _Add files to index:_   
        `git add *changed files with __code__`
   * _Commit changes and write __meaningful__ commit message:_
        `git commit`
   * _Push to remote:_
        `git push`
   * _....create pull request on [Github](https://github.com/smay1613/LTC-STL-Student/pulls)...._
   * _Switch back to master branch:_
        `git checkout master`
