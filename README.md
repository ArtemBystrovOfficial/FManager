# ![logo](https://user-images.githubusercontent.com/92841151/194349274-67019ddb-81a4-4d17-a03f-7e52cb541845.png) FManager - manage your [FServer 2.0](https://github.com/ArtemBystrovOfficial/FServer2.0) project faster

<span>
<img src ="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black"/>
<img src ="https://img.shields.io/badge/mac%20os-000000?style=for-the-badge&logo=apple&logoColor=white"/>
<img src ="https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white"/>
</span>

## For what?

```diff
! The Server 2.0 library is a medium level of abstraction. 
```

```diff
+ But you can independently think of a plan to create your server separate from the client
+ And use console interface, which setup in cpp.
```
```diff
- If you want to use 6 level of OSI and more, please download useful additions from FTools repository

```
## Interface

```
╒════════════════╕   ┆ [IO]: >> recive from 2 is_command: 0 struct MainPocket { msg : 7023 } 4 bytes
|      Logs      | ->┆ [IO]: << send to 1 is_command: 0 struct MainPocket { msg : 16986 } 4 bytes
╘════════════════╛   ┆ [BASIC] fid 1 disconected
 ────────────────    ┆ [IO]: << send to 2 is_command: 0struct MainPocket { msg : 16990 } 4 bytes
    Start/Pause      ┆ [BASIC] fid 3 connected
 ────────────────    ╰──────────────────────────────────────────────────────────────────────────────── 
 ────────────────    ╒════════════════╕ ────────────────   Online List
      Online      -- |  Online list   |      Fid IP       1  127.0.0.1 
 ────────────────    ╘════════════════╛ ────────────────  3  134.56.2.45 
 ────────────────    ╒════════════════╕ ────────────────  ────────────────     Ban List
       Bans       -- |     Ban IP     |     Unban IP          Ban List      192.168.0.231
 ────────────────    ╘════════════════╛ ────────────────  ────────────────
 ────────────────     ────────────────  ──────────────── ╒════════════════╕    Groups list
      Groups      --    Add to group       New group     | List of groups |  gid: 1 fid: 2 5 7
 ────────────────     ────────────────  ──────────────── ╘════════════════╛  gid: 2 fid: 1 
 ────────────────
     Refresh      <->
 ────────────────
 ────────────────
       Off
 ────────────────
 ENTER - Refresh/Entry | ESC - Return | UP / DOWN - MOVE
```
## Install

- 'clone' repository on `Linux` or `Windows`
- download submodules git `submodule update --init --force --remote`
- use 'cmake' and 'make' for build
- try testing 'build/app' on your platform
```diff
- not edit files, if you want more free, use FServer 2.0
```
- go to next steps
____
## Configure
`MainPocket.hpp` - edit your pocket how you need it, make any static members of classes, which you need to send

```c++
#pragma once

struct MainPocket
{

    //There your data
    
//DON'T EDIT BELOW

    friend std::string & operator+=(std::string& left, const MainPocket& pocket);
};

std::string & operator+=(std::string& left,const MainPocket& pocket);

```   
                                                                                      
`MainPocket.cpp` - add to string your information about pocket, which you can see at Logs in `manager` 
```c++                                                                                
#include "MainPocket.hpp"

std::string& operator+=(std::string& log, const MainPocket& pocket)
{

    log += "n : "; 
    log += std::to_string(pocket.n);

    // Before your logs operator for struct

    return log;
}
```

`Config.cpp` - main off manager all logic write this, use this like [FServer2.0 | Doc](https://github.com/ArtemBystrovOfficial/FServer2.0) but:
- *srv - member of FServer use all operations with him
- manager clean himself after work, you can not care about it
- 3 rules which make your work easy:
  - start with `srv->start()`;
  - use `while (!_exit_app.load()) {}` for loop recv
  - using `Out` for <<

```c++
#include "FManager.hpp"

using Out = _Out<MainPocket>;

void FManager::realisationOfCLogic() { 
	
	srv->start();

	std::pair <MainPocket, int > pocket_recv;

	while (!_exit_app.load()) {

		*srv >> pocket_recv;

		auto& [pocket, fid] = pocket_recv;

		pocket.n *= 2;

		*srv << Out{ pocket , FType::FID, fid };

	}

}

```
_________

## Feedback
:email: bystrov.official.one@gmail.com

![logo](https://user-images.githubusercontent.com/92841151/163685103-54875fdc-2b7d-4e54-b73e-6564479622c6.png)

