# FManager - manage your FServer 2.0 project faster

<span>
<img src ="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black"/>
<img src ="https://img.shields.io/badge/mac%20os-000000?style=for-the-badge&logo=apple&logoColor=white"/>
<img src ="https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white"/>
</span>

## For what?

```diff
! The Server 2.0 library is a medium level of abstraction. <br/>
```

```diff
+ But you can independently think of a plan to create your server separate from the client
+ And use console interface, which setup in cpp.
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
## install



