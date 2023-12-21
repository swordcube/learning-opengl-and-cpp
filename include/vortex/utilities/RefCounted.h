#pragma once

namespace vortex {
    class RefCounted {
        public:
            RefCounted();
            virtual ~RefCounted();

            int getReferences();
            void reference();
            void unreference();

        private:
            int references = 0;
    };
}