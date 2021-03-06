"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

import kinect.point3d_t

class link_msg_t(object):
    __slots__ = ["joint_id", "source", "dest"]

    def __init__(self):
        self.joint_id = 0
        self.source = kinect.point3d_t()
        self.dest = kinect.point3d_t()

    def encode(self):
        buf = BytesIO()
        buf.write(link_msg_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">i", self.joint_id))
        assert self.source._get_packed_fingerprint() == kinect.point3d_t._get_packed_fingerprint()
        self.source._encode_one(buf)
        assert self.dest._get_packed_fingerprint() == kinect.point3d_t._get_packed_fingerprint()
        self.dest._encode_one(buf)

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != link_msg_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return link_msg_t._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = link_msg_t()
        self.joint_id = struct.unpack(">i", buf.read(4))[0]
        self.source = kinect.point3d_t._decode_one(buf)
        self.dest = kinect.point3d_t._decode_one(buf)
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if link_msg_t in parents: return 0
        newparents = parents + [link_msg_t]
        tmphash = (0xe071115012961010+ kinect.point3d_t._get_hash_recursive(newparents)+ kinect.point3d_t._get_hash_recursive(newparents)) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff)  + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if link_msg_t._packed_fingerprint is None:
            link_msg_t._packed_fingerprint = struct.pack(">Q", link_msg_t._get_hash_recursive([]))
        return link_msg_t._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

