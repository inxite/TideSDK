/**
 * Copyright (c) 2012 - 2014 TideSDK contributors 
 * http://www.tidesdk.org
 * Includes modified sources under the Apache 2 License
 * Copyright (c) 2008 - 2012 Appcelerator Inc
 * Refer to LICENSE for details of distribution and use.
 **/

#ifndef _DELEGATING_OBJECT_H_
#define _DELEGATING_OBJECT_H_

#include <vector>
#include <string>
#include <map>

#include <Poco/Mutex.h>

namespace tide
{
    /**
     * The DelegatingObject lets you wrap a globally accessible
     * object in such a way as it appears to have special properties in
     * in local contexts. When a Get(...) occurs, the object searches a local
     * delegate and then a global one. When a Set(...) occurs, the object
     * performs it on both the local and the global version. Thus this object
     * is most useful if the local properties are assigned to the local object
     * in an initial setup phase.
     */
    class TIDE_API DelegatingObject : public TiObject
    {
        public:
        DelegatingObject(TiObjectRef global);
        DelegatingObject(TiObjectRef global, TiObjectRef local);
        virtual ~DelegatingObject();
        virtual ValueRef Get(const char *name);
        virtual SharedStringList GetPropertyNames();
        virtual void Set(const char *name, ValueRef value);
        virtual bool HasProperty(const char* name);

        virtual inline TiObjectRef GetGlobal() { return this->global; }
        virtual inline TiObjectRef GetLocal() { return this->local; }

        private:
        /**
         * The global part of this delegate object. This object
         * is used to find properties if they are not found in
         * the local object.
         */
        TiObjectRef global;

        /**
         * The local part of this delegate object. This object
         * is the first in line for property retrieval. 
         */
        TiObjectRef local;

        DISALLOW_EVIL_CONSTRUCTORS(DelegatingObject);

    protected:
        Poco::Mutex mutex;
    };
}

#endif
