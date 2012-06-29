Buckets
=======

The bucket system is prepared in such a way that data buffers can me moved
with ease and support many modes of transfer.

Buckets are effectively pointer to buffers, but may also represent data
sourced from a stream that may support effective transfer to certain sinks.
An example of such a bucket is one sourced from a file descriptor and then
written to another file descriptor. Depending on the sources/destination
file descriptor type, sendfile could be used to transfer the data, avoiding
the memory buffers from being allocated and used in userspace.

Bucket State Information
========================

 * is-read-write
 * is-read-only
 * is-write-only

File Bucket Information
+++++++++++++++++++++++

 * fd
 * is-socket

Bucket Operations
=================


Streams
=======

Steams abstract stream operations on top of buckets, such as:
 * read
   * to bucket
   * to stream
   * to buffer
 * write
   * from bucket
   * from stream
   * from buffer

Filters
=======

Filters abstract operations on top of buckets and streams.

Some filters can accept multiple input/output streams.
