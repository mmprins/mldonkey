(* Copyright 2002 b8_bavard, b8_fee_carabine, INRIA *)
(*
    This file is part of mldonkey.

    mldonkey is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    mldonkey is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with mldonkey; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*)

val clients_by_id :  (Ip.t, ServerTypes.client) Hashtbl.t
val files_by_md4 : (Md4.t, ServerTypes.location list) Hashtbl.t 
val servers_by_md4 : (Md4.t, ServerTypes.server) Hashtbl.t
val client_counter : int ref
val other_servers : ServerTypes.server list ref
val alive_servers : ServerTypes.server list ref
val nconnected_clients : int ref
val nshared_files : int ref

(*test values*)
val nb_udp_loc : int ref
val nb_udp_req : int ref
val nb_udp_query : int ref
val nb_tcp_req : int ref
  