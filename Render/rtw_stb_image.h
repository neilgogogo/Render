//
//  rtw_stb_image.h
//  Render
//
//  Created by Neil Li on 2020/4/27.
//  Copyright © 2020 Neil Li. All rights reserved.
//

#ifndef rtw_stb_image_h
#define rtw_stb_image_h

// Disable pedantic warnings for this external library.
#ifdef _MSC_VER
    // Microsoft Visual C++ Compiler
    #pragma warning (push, 0)
#endif



#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"


// Restore warning levels.
#ifdef _MSC_VER
    // Microsoft Visual C++ Compiler
    #pragma warning (pop)
#endif


#endif /* rtw_stb_image_h */
