"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

class projected_point2d_t(object):
    __slots__ = ["u", "v"]

    def __init__(self):
        self.u = 0.0
        self.v = 0.0

    def encode(self):
        buf = BytesIO()
        buf.write(projected_point2d_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">ff", self.u, self.v))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != projected_point2d_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return projected_point2d_t._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = projected_point2d_t()
        self.u, self.v = struct.unpack(">ff", buf.read(8))
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if projected_point2d_t in parents: return 0
        tmphash = (0x7f2d87baacd686d7) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff)  + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if projected_point2d_t._packed_fingerprint is None:
            projected_point2d_t._packed_fingerprint = struct.pack(">Q", projected_point2d_t._get_hash_recursive([]))
        return projected_point2d_t._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

