# CoreCLR.ZeroGC
Zero Garbage Collector for CoreCLR

Starting from .NET Core 2.0 coupling between Garbage Collector and the Execution Engine itself have been loosened. Prior to this version, the Garbage Collector code was pretty much tangled with the rest of the CoreCLR code. However, Local GC initiative in version 2.0 is already mature enough to start using it. The purpose of the exercise we are going to do is to prepare Zero Garbage Collector that replaces the default one.

Zero Garbage Collector is the simplest possible implementation that in fact does almost nothing. It only allows you to allocate objects, because this is obviously required by the Execution Engine. Created objects are never automatically deleted and theoretically, no longer needed memory is never reclaimed. Why one would be interested in such a simple GC implementation? There are at least two reasons:
* it is an excellent basis for the development of your own Garbage Collection mechanism. It provides the necessary functionality to make runtime work properly and you can build on top of that.
* it may be interesting for special use cases like very short living applications or such that almost no allocate memory (you can come up with those concepts as No-alloc or Zero-alloc programming). In such case providing GC overhead is unnecessary and it may be wise to get rid of it. It is like making huge GC.TryStartNoGCRegion over all you application.

You can find detailed description of the project:
* [Zero Garbage Collector for .NET Core](http://tooslowexception.com/zero-garbage-collector-for-net-core)
* [Zero Garbage Collector for .NET Core 2.1 and ASP.NET Core 2.1](http://tooslowexception.com/zero-garbage-collector-for-net-core-2-1-and-asp-net-core-2-1/)