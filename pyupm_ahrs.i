// Include doxygen-generated documentation
%include "pyupm_doxy2swig.i"
%module pyupm_ahrs
%include "../upm.i"
%include "cpointer.i"

%include "stdint.i"

%feature("autodoc", "3");

%pointer_functions(float, floatp);

%include "ahrs.hpp"
%{
    #include "ahrs.hpp"
%}

