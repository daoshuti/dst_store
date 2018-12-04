" --------------------------------------------------------------------
" Owner: 王涵
" Email: daoshuti@163.com
" Github: https://github.com/daoshuti
" --------------------------------------------------------------------

" GENERAL SETTINGS:
" {{{1

" To use VIM settings, out of VI compatible mode.
set nocompatible

" Set Dos Mode
if has('win32') || has('win64')
    set runtimepath=$HOME/.vim,$VIM/vimfiles,$VIMRUNTIME,$VIM/vimfiles/after,$HOME/.vim/after
endif

" Pathogen
" 启动pathogen插件管理器
execute pathogen#infect() 

" Syntax highlighting.
if has("syntax")
    syntax on
endif

" Enable file type detection.
filetype on
filetype plugin indent on " 开启三个功能：文件类型检查、插件、缩进

" Other settings.
set autoindent		" 创建新行自动缩进
set cindent			" 开启针对c文件的缩进
set smartindent	    " 开启智能缩进，它不像cindent那样完美支持c文件的缩进，但对于未知类型文件的缩进，还是有帮助的
set autoread		" 文件在Vim之外修改过，自动重新读入
set autowrite
set backspace=indent,eol,start
set cinoptions=:0
set cursorline		" 为光标所在行加下划线
set completeopt=longest,menuone
set fileencodings=utf-8,gb2312,gbk,gb18030 " 使用utf-8或gbk等编码打开文件
set fileformat=unix
set foldenable
set foldmethod=marker	" 代码折叠(标签折叠方式)
"set foldmethod=indent	" 代码折叠（缩进折叠方式）
"set foldmethod=syntax	" 代码折叠（语法折叠方式）
set foldcolumn=0		" 每行前面有0个折叠标识列
set helpheight=10
set helplang=cn       " 帮助系统设置为中文
set hidden
set history=1000      " 历史记录保留1000条
set hlsearch
set ignorecase        " 检索时忽略大小写
set incsearch
set laststatus=2      " 指定何时显示状态行
"                          " 0 永远没有
"                          " 1 只有分割窗口时(默认值)
"                          " 2 总是存在
set mouse=a         " 可以使用鼠标
set number          " 显示行号
set pumheight=10
set ruler           "显示状态栏
set scrolloff=5
set showcmd
set smartcase
set tabstop=4       " 制表符为4
set noexpandtab     " 不把制表符替换为空格
"set expandtab       " 制表符替换为空格
set shiftwidth=0    "换行时使用0个空格，使用tab键风格时如此设置
"set shiftwidth=4    "换行时使用4个空格
set termencoding=utf-8
set whichwrap=h,l
set wildignore=*.bak,*.o,*.e,*~
set wildmenu
set wildmode=list:longest,full
set nowrap          " 禁止文字自动换行
"set textwidth=256   " 超过256个字符自动换行
set nobackup
set noswapfile      " 不使用swapfile文件（不能灾难恢复）

" gui settings
if has("gui_running")
    "set guioptions-=m " no menubar 将Gvim中的菜单栏去除
    set guioptions-=T " no toolbar 将Gvim中的工具栏去除
    set guioptions-=r " no right-hand scrollbar 将右边的滚动条去除
    set guioptions-=R " no right-hand vertically scrollbar 将右边的垂直滚动条去除
    set guioptions-=l " no left-hand scrollbar 将左边的滚动条去除
    set guioptions-=L " no left-hand vertically scrollbar 将左边边的垂直滚动条去除
    autocmd GUIEnter * simalt ~x " window width and height
    source $VIMRUNTIME/delmenu.vim " the original menubar has an error on win32, so
    source $VIMRUNTIME/menu.vim    " use this menubar
    language messages zh_CN.utf-8 " use chinese messages if has
    set guifont=Consolas:h14
endif

" }}}1
" AUTO COMMANDS:
" {{{1

autocmd BufNewFile *.c,*.cpp,*.sh,*.py,*.java exec ":call SetTitle()"                                                                                       
"定义函数SetTitle，自动插入文件头
func SetTitle()
    "如果文件类型为.c或者.cpp文件
    if (&filetype == 'c' || &filetype == 'cpp')
        call setline(1, "/*************************************************************************")
        call setline(2, "\ @Author: wanghan")
        call setline(3, "\ @Created Time : ".strftime("%c"))
        call setline(4, "\ @File Name: ".expand("%"))
        call setline(5, "\ @Description:")
        call setline(6, " ************************************************************************/")
        call setline(7,"")
    endif
    "如果文件类型为.sh文件
    if &filetype == 'sh'
        call setline(1, "\#!/bin/bash")
        call setline(2, "\# Author: wanghan")
        call setline(3, "\# Created Time : ".strftime("%c"))
        call setline(4, "\# File Name: ".expand("%"))
        call setline(5, "\# Description:")
        call setline(6,"")
    endif
    "如果文件类型为.py文件
    if &filetype == 'python'
        call setline(1, "\#!/usr/bin/env python")
        call setline(2, "\# -*- coding=utf8 -*-")
        call setline(3, "\"\"\"")
        call setline(4, "\# Author: wanghan")
        call setline(5, "\# Created Time : ".strftime("%c"))
        call setline(6, "\# File Name: ".expand("%"))
        call setline(7, "\# Description:")
        call setline(8, "\"\"\"")
        call setline(9,"")
    endif
    "如果文件类型为.java文件
    if &filetype == 'java'
        call setline(1, "//coding=utf8")
        call setline(2, "/**")
        call setline(3, "\ *\ @Author: wanghan")
        call setline(4, "\ *\ @Created Time : ".strftime("%c"))
        call setline(5, "\ *\ @File Name: ".expand("%"))
        call setline(6, "\ *\ @Description:")
        call setline(7, "\ */")
        call setline(8,"")
    endif
endfunc
" 自动将光标定位到末尾
autocmd BufNewFile * normal G

" }}}1
" SYSTEM SHORTCUT SETTINGS:
" {{{1
" Set mapleader
let mapleader=","
" Space to command mode.
nnoremap <space> :
vnoremap <space> :
" Switching between buffers.
"nnoremap <C-h> <C-W>h
"nnoremap <C-j> <C-W>j
"nnoremap <C-k> <C-W>k
"nnoremap <C-l> <C-W>l
" }}}1
" PLUGINS SETTINGS:
" {{{1

" Setting background 设置vim背景颜色
set   background=dark " 配色主题的色系设置为dark
"set   background=light " 配色主题的色系设置为light

" Setting colorscheme 设置vim配色主题
"colorscheme industry " 配色主题的名称设置为industry
"colorscheme solarized " 配色主题的名称设置为solarized
"let g:solarized_termcolors=256

" Markdown插件
autocmd BufNewFile,BufReadPost *.md set filetype=markdown
let g:markdown_fenced_languages = ['html', 'python', 'bash=sh']
"let g:markdown_syntax_conceal = 0 "关闭Markdown语法高亮
"let g:markdown_minlines = 100 "支持100行显示（默认50行），开启后可能会卡

" 配置rainbow插件
" 显示彩色的括号
let g:rainbow_active = 1 "0 if you want to enable it later via :RainbowToggle
let g:rainbow_conf = {
            \	'guifgs': ['royalblue3', 'darkorange3', 'seagreen3', 'firebrick'],
            \	'ctermfgs': ['lightblue', 'lightyellow', 'lightcyan', 'lightmagenta'],
            \	'operators': '_,_',
            \	'parentheses': ['start=/(/ end=/)/ fold', 'start=/\[/ end=/\]/ fold', 'start=/{/ end=/}/ fold'],
            \	'separately': {
            \		'*': {},
            \		'tex': {
            \			'parentheses': ['start=/(/ end=/)/', 'start=/\[/ end=/\]/'],
            \		},
            \		'lisp': {
            \			'guifgs': ['royalblue3', 'darkorange3', 'seagreen3', 'firebrick', 'darkorchid3'],
            \		},
            \		'vim': {
            \			'parentheses': ['start=/(/ end=/)/', 'start=/\[/ end=/\]/', 'start=/{/ end=/}/ fold', 'start=/(/ end=/)/ containedin=vimFuncBody', 'start=/\[/ end=/\]/ containedin=vimFuncBody', 'start=/{/ end=/}/ fold containedin=vimFuncBody'],
            \		},
            \		'html': {
            \			'parentheses': ['start=/\v\<((area|base|br|col|embed|hr|img|input|keygen|link|menuitem|meta|param|source|track|wbr)[ >])@!\z([-_:a-zA-Z0-9]+)(\s+[-_:a-zA-Z0-9]+(\=("[^"]*"|'."'".'[^'."'".']*'."'".'|[^ '."'".'"><=`]*))?)*\>/ end=#</\z1># fold'],
            \		},
            \		'css': 0,
            \	}
            \}

" 配置Taglist插件
let g:Tlist_Auto_Open=0				" 1为默认打开Taglist窗口
let g:Tlist_Auto_Update=1			" 打开/禁止Taglist在打开新文件或修改文件后自动更新标签。禁止自动更新后，Taglist仅在使用:TlistUpdate,:TlistAddFiles，或:TlistAddFilesRecursive命令后更新标签
let g:Tlist_Process_File_Always=1	" Taglist始终解析文件中的tag，不管Taglist窗口有没有打开
let g:Tlist_Exit_OnlyWindow=1		" 只有剩一个窗口且是Taglist时，自动退出
let g:Tlist_Show_One_File=1			" Taglist只显示一个文件
"let g:Tlist_File_Fold_Auto_Close=1	" 当设置为１，当同时显示多个文件中的tag时，可使taglist只显示当前文件tag，其它文件的tag都被折叠起来
"let g:Tlist_Highlight_Tag_On_BufEnter=1     " 默认情况下，Vim打开/切换至一个新的缓冲区/文件后，标签列表窗口会自动将当前代码窗口对应的标签高亮显示。TlistHighlight_Tag_On_BufEnter置为0可禁止以上行为
let g:Tlist_WinWidth=50				" 设置Taglist的宽度为50
let g:Tlist_Enable_Fold_Column=0	" 不要显示折叠树
let g:Tlist_Auto_Highlight_Tag=1	" 自动高亮Taglist窗口中选中的Tag

" 配置NERDTree插件
let Tlist_Show_One_File=1
let g:NERDTreeWinPos="right"
let g:NERDTreeWinSize=25
let g:NERDTreeShowLineNumbers=1
let g:NERDTreeQuitOnOpen=1

" 配置CrtlP插件
let g:ctrlp_map = '<c-p>'
let g:ctrlp_cmd = 'CtrlP'

" 配置cscope
if has("cscope")
    set csto=1
    set cst
    set nocsverb
    if filereadable("cscope.out")
        cs add cscope.out
    endif
    set csverb
endif

" 配置OmniCppComplete插件
"set nocompatible or set nocp "关闭vi兼容模式(通用设置中已经开启)
"filetype plugin on "文件类型检查(通用设置中已经开启)
let g:OmniCpp_DefaultNamespaces=["std"]
let g:OmniCpp_MayCompleteScope=1
let g:OmniCpp_SelectFirstItem=2
" 生成标签文件命令
" 	ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .
" 在对C++文件进行补全时，OmniCppComplete插件需要tag文件中包含C++的额外信息，因此上面的ctags命令不同于以前我们所使用的，它专门为C++语言生成一些额外的信息，上述选项的含义如下：
" 	--c++-kinds=+p : 为C++文件增加函数原型的标签
" 	--fields=+iaS : 在标签文件中加入继承信息(i)、类成员的访问控制信息(a)、以及函数的指纹(S)
" 	--extra=+q : 为标签增加类修饰符。注意，如果没有此选项，将不能对类成员补全

" Man.vim Man手册插件 这个插件是vim自带的
source $VIMRUNTIME/ftplugin/man.vim

" snipmate插件 代码补全（从vim官网下载，不是github）
" 补全c\cpp\java\ruby等问题

" acp插件 代码提示
" 智能显示代码提示

" auto-pairs插件
" 括号自动补全()[]{}

" 设定中文doc帮助文档目录
"let helptags="$VIM/bundle/vimcdoc/doc"
"set helplang=cn "设定帮助系统设置为中文

" }}}1
" PLUGIN SHORTCUT SETTINGS:
" {{{1

" <F9><F10><F12>快捷键依赖的运行shell脚本的函数
function! RunShell(Msg, Shell)
    echo a:Msg . '...'
    call system(a:Shell)
    echon ' [Done]'
endfunction

let s:f6_flag=0
let s:f7_flag=0
" <F6>快捷键依赖的运行vimscript脚本的函数
function F6_shell()
    if (s:f6_flag == 0)
        set paste
        set nonumber
        if (s:f7_flag == 1)
            set foldcolumn=0
            set foldmethod=marker
        endif
        let s:f6_flag=1
    else
        set nopaste
        set number
        if (s:f7_flag == 1)
            set foldcolumn=5
            set foldmethod=indent
        endif
        let s:f6_flag=0
    endif
endfunction


" <F7>快捷键依赖的运行vimscript脚本的函数
function F7_shell()
    if (s:f7_flag == 0)
        set foldcolumn=5
        set foldmethod=indent
        let s:f7_flag=1
    else
        set foldcolumn=0
        set foldmethod=marker
        let s:f7_flag=0
    endif
endfunction

" ------------------
" <Fx>类型快捷键
" ------------------
" <F2> 左侧，Tlist 窗口
" <F3> 右侧，文件浏览窗口
" <F4> 下方，查看最近的浏览记录
" <F5> CtrlP模式下刷新缓存（CtrlP插件自带）
" <F6> 粘贴模式
" <F7> 切换代码折叠方式（maker改为indent）
" <F9> 生成tags数据库文件。之后就可以使用ctrl+] 和 ctrl+o(或者ctrl+t)
" <F10> 以绝对路径在当前目录下，生成cscope数据库文件<目录名.out>
" <F12> 生成cscope.out数据库文件
nmap  <F2> :TlistToggle<cr>
nmap  <F3> :NERDTreeToggle<cr>
nmap  <F4> :MRU<cr>
nmap  <F6> :call F6_shell()<cr>
nmap  <F7> :call F7_shell()<cr>
nmap  <F9> :call RunShell("Generate tags", "ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .")<cr>
nmap <F10> :call RunShell("本地生成cscope文件", "bash ~/.vim/shell/create_cscope.sh")<cr>
nmap <F12> :call RunShell("Generate cscope", "cscope -Rb")<cr>:cs add cscope.out<cr>

" ------------------
" <leader>类型快捷键
" ------------------
" Cscope命令说明：
" cscope add cscope.out --- 添加cscope.out文件
" cscope find s --- 查找C语言符号，即查找函数名、宏、枚举值等出现的地方
" cscope find g --- 查找函数、宏、枚举等定义的位置，类似ctags所提供的功能
" cscope find d --- 查找本函数调用的函数
" cscope find c --- 查找调用本函数的函数
" cscope find t --- 查找指定的字符串
" cscope find e --- 查找egrep模式，相当于egrep功能，但查找速度快多了
" cscope find f --- 查找并打开文件，类似vim的功能
" cscope find i --- 查找包含本文件的文件
" ------------------------------------------------------------------
"	USAGE	:cs add {file|dir} [pre-path] [flags]
"
"	USAGE	:cs find {querytype} {name}
"		0 or s: Find this C symbol
"		1 or g: Find this definition
"		2 or d: Find functions called by this function
"		3 or c: Find functions calling this function
"		4 or t: Find this text string
"		6 or e: Find this egrep pattern
"		7 or f: Find this file
"		8 or i: Find files #including this file
nmap <leader>sa :cs add cscope.out<cr>
nmap <leader>ss :cs find s <C-R>=expand("<cword>")<cr><cr>
nmap <leader>sg :cs find g <C-R>=expand("<cword>")<cr><cr>
nmap <leader>sd :cs find d <C-R>=expand("<cword>")<cr><cr>
nmap <leader>sc :cs find c <C-R>=expand("<cword>")<cr><cr>
nmap <leader>st :cs find t <C-R>=expand("<cword>")<cr><cr>
nmap <leader>se :cs find e <C-R>=expand("<cword>")<cr><cr>
nmap <leader>sf :cs find f <C-R>=expand("<cfile>")<cr><cr>
nmap <leader>si :cs find i <C-R>=expand("<cfile>")<cr><cr>

",c 创建新标签
",x 删除标签
",[ 移动到前一个标签
",] 移动到下一个标签
nmap <leader>c :tabnew<cr>
nmap <leader>x :tabclose<cr>
nmap <leader>] :tabn<cr>
nmap <leader>[ :tabp<cr>

" 折叠全文只留下查找结果
" 先使用普通的/或者?进行查找，然后按下zs就进入视线折叠了
" zO局部展开
" zC重新折叠
" zR快捷键恢复
" zS目录结构恢复原状
nnoremap zs :setlocal foldexpr=(getline(v:lnum)=~@/)?0:(getline(v:lnum-1)=~@/)\\|\\|(getline(v:lnum+1)=~@/)?1:2 foldmethod=expr foldlevel=0 foldcolumn=2<CR>:set foldmethod=manual<CR><CR>
nnoremap zS :set foldcolumn=0<CR>:set foldmethod=marker<CR><CR>

" 添加tags文件(以便使用代码跳转和补全)
"set tags+=/usr/include/tags
"set tags+=./tags

" }}}1

