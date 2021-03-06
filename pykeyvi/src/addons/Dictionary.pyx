

    def get (self, key, default = None):
        assert isinstance(key, bytes), 'arg in_0 wrong type'
    
        cdef _Match * _r = new _Match(deref(self.inst.get())[(<const_char *>key)])

        if _r.IsEmpty():
            return default
        cdef Match py_result = Match.__new__(Match)
        py_result.inst = shared_ptr[_Match](_r)
        return py_result

    def __contains__(self, key):
        assert isinstance(key, bytes), 'arg in_0 wrong type'

        return self.inst.get().Contains(key)

    def __len__(self):
        return self.inst.get().GetSize()

    def __getitem__ (self, key):
        assert isinstance(key, bytes), 'arg in_0 wrong type'
    
        cdef _Match * _r = new _Match(deref(self.inst.get())[(<const_char *>key)])

        if _r.IsEmpty():
            raise KeyError(key)
        cdef Match py_result = Match.__new__(Match)
        py_result.inst = shared_ptr[_Match](_r)
        return py_result

    def _key_iterator_wrapper(self, iterator):
        for m in iterator:
            yield m.GetMatchedString()

    def _value_iterator_wrapper(self, iterator):
        for m in iterator:
            yield m.GetRawValueAsString()

    def _item_iterator_wrapper(self, iterator):
        for m in iterator:
            yield (m.GetMatchedString(), m.GetRawValueAsString())

    def GetAllKeys(self):
        cdef _MatchIteratorPair _r = self.inst.get().GetAllItems()
        cdef MatchIterator py_result = MatchIterator.__new__(MatchIterator)
        py_result.it = _r.begin()
        py_result.end = _r.end()
        return self._key_iterator_wrapper(py_result)

    def GetAllValues(self):
        cdef _MatchIteratorPair _r = self.inst.get().GetAllItems()
        cdef MatchIterator py_result = MatchIterator.__new__(MatchIterator)
        py_result.it = _r.begin()
        py_result.end = _r.end()
        return self._value_iterator_wrapper(py_result)

    def GetAllItems(self):
        cdef _MatchIteratorPair _r = self.inst.get().GetAllItems()
        cdef MatchIterator py_result = MatchIterator.__new__(MatchIterator)
        py_result.it = _r.begin()
        py_result.end = _r.end()
        return self._item_iterator_wrapper(py_result)

    def GetManifest(self):
        cdef libcpp_string _r = self.inst.get().GetManifestAsString()
        cdef bytes py_result = _r
        import json
        return json.loads(py_result)

    def GetStatistics(self):
        cdef libcpp_string _r = self.inst.get().GetStatistics()
        cdef bytes py_result = _r
        import json
        return {k: json.loads(v) for k, v in filter(
            lambda kv: kv and isinstance(kv, list) and len(kv) > 1 and kv[1],
            [s.rstrip().split("\n") for s in py_result.split("\n\n")]
        )}
