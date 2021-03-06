//-----------------------------------------------------------------------------
//  (c) 2006 by Basler Vision Technologies
//  Section: Vision Components
//  Project: GenApi
//  Author:  Fritz Dierks
//  $Header: /cvs/genicam/genicam/library/CPP/include/GenApi/IValue.h,v 1.13 2007/08/16 13:56:41 hartmut_nebelung Exp $
//
//  License: This file is published under the license of the EMVA GenICam  Standard Group. 
//  A text file describing the legal terms is included in  your installation as 'GenICam_license.pdf'. 
//  If for some reason you are missing  this file please contact the EMVA or visit the website
//  (http://www.genicam.org) for a full copy.
// 
//  THIS SOFTWARE IS PROVIDED BY THE EMVA GENICAM STANDARD GROUP "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,  
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR  
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE EMVA GENICAM STANDARD  GROUP 
//  OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  SPECIAL, 
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT  LIMITED TO, 
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  DATA, OR PROFITS; 
//  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  THEORY OF LIABILITY, 
//  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE) 
//  ARISING IN ANY WAY OUT OF THE USE  OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
//  POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------
/*!
\file
\brief    Definition of the interface IValue.
\ingroup GenApi_PublicInterface
*/

#ifndef GENAPI_IVALUE_H
#define GENAPI_IVALUE_H

#include "GenApiDll.h"
#include "Types.h"
#include "IBase.h"
#include "INode.h"
#include <Base/GCString.h>
#include <Base/GCException.h>

#pragma warning ( push )
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY

namespace GenApi
{
    interface INode;

    //*************************************************************
    // IValue interface
    //*************************************************************

    /**
    \brief Interface for value properties
    \ingroup GenApi_PublicInterface
    */
    interface   IValue : virtual public IBase
    {
        //! Get the INode interface of the node
        virtual INode* GetNode() { return dynamic_cast<INode*>(this); }

        //! Get content of the node as string
        virtual GenICam::gcstring ToString(bool Verify = false) = 0;

        //! Set content of the node as string
        virtual void FromString(const GenICam::gcstring& ValueStr, bool Verify = true) = 0;
    };


    //*************************************************************
    // CValueRef class
    //*************************************************************

    /**
    \internal
    \brief Reference to an IValue pointer
    \ingroup GenApi_PublicImpl
    */
    template <class T>
    class CValueRefT : public CBaseRefT<T>
    {
    	typedef CBaseRefT<T> ref;
	
    public:
        /*--------------------------------------------------------*/
        // IValue
        /*--------------------------------------------------------*/

        //! Get the INode interface of the node
        virtual INode* GetNode() 
        {
            if(ref::m_Ptr)
                return ref::m_Ptr->GetNode();
            else
                throw ACCESS_EXCEPTION("Feature not present (reference not valid)");
        }

        //! Get content of the node as string
        virtual GenICam::gcstring ToString(bool Verify = false)
        {
            if(ref::m_Ptr)
                return ref::m_Ptr->ToString(Verify);
            else
                throw ACCESS_EXCEPTION("Feature not present (reference not valid)");
        }

        //! Set content of the node as string
        virtual void FromString(const GenICam::gcstring& ValueStr, bool Verify = true)
        {
            if(ref::m_Ptr)
                return ref::m_Ptr->FromString(ValueStr, Verify);
            else
                throw ACCESS_EXCEPTION("Feature not present (reference not valid)");
        }

    };

    //! Reference to an IValue pointer
    //! \ingroup GenApi_PublicImpl
    typedef CValueRefT<IValue> CValueRef;  

}

#pragma warning ( pop )

#endif // ifndef GENAPI_IVALUE_H
