%module jsupm_ahrs
%include "../upm.i"
%include "cpointer.i"

%pointer_functions(float, floatp);

%include "ahrs.hpp"
%{
    #include "ahrs.hpp"
%}

