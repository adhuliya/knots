Network Setup
=================

* See the IP address and names of all the active interfaces:

        ip addr        # method 1
        ifconfig       # method 2

* See all the interfaces:

        ip link show   # method 1
        ifconfig -a    # method 2 - `-a` displays interfaces even if its down

* For dynamic configuration of interface `wlp3s0`,
  add the following lines to `/etc/network/interfaces`:

        #Configuration for interface wlp3s0
        auto wlp3s0
        iface wlp3s0 inet dhcp

* For static configuration of interface `wlp3s0`,
  add the following lines to `/etc/network/interfaces`:

        #Configuration for interface wlp3s0
        auto wlp3s0
        iface wlp3s0 inet static
        address 192.168.1.151
        netmask 255.255.255.0
        gateway 192.168.1.1
        dns-nameservers 10.200.1.11

  In some systems `dns-nameserver` works (each nameserver in its own line) 
  instead of `dns-nameservers` (which accomodates all space-separated nameservers in 
  a single line) (Not experienced this yet).

* To bring the settings of `/etc/network/interfaces` into
  effect do:

        sudo systemctl restart NetworkManager

* see `man interfaces` on info on `/etc/network/interfaces`
* Read from this source: <https://www.tecmint.com/linux-networking-commands/>
* See Chapter 4 in : <https://help.ubuntu.com/lts/serverguide/serverguide.pdf>
* Check if this i useful: <http://www.haifux.org/lectures/172/netLec.pdf>


