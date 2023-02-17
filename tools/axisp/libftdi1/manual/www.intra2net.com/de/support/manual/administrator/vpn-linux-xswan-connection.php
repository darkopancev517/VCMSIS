<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Verbindungen konfigurieren | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="vpn-linux-xswan.php" title="53. Kapitel - VPN mit Linux"><link rel="prev" href="vpn-linux-xswan-cert.php" title="53.2. Zertifikate erzeugen"><link rel="next" href="vpn-linux-xswan-intranator.php" title="53.4. Intranator">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="vpn-linux-xswan-connection.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="vpn-linux-xswan-connection.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">53.3. Verbindungen konfigurieren</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="vpn-linux-xswan-cert.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">53. Kapitel - VPN mit Linux</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="vpn-linux-xswan-intranator.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="vpn-linux-xswan-connection"></a>53.3. Verbindungen konfigurieren</h2></div></div></div><div class="orderedlist"><ol type="1"><li><p>Lassen Sie sich den Inhalt der Datei <code class="filename">/etc/ipsec.conf</code> ausgeben.
          Sie sollten hier die Zeile <code class="computeroutput">include /etc/ipsec.d/*.conf</code>
          finden. Sie darf nicht mit dem Zeichen <code class="computeroutput">#</code> beginnen, denn
          ansonsten w&auml;re sie auskommentiert.</p></li><li><p>Lassen Sie sich den Inhalt der Datei <code class="filename">/etc/ipsec.secrets</code> ausgeben.
          Sie sollten hier die Zeile <code class="computeroutput">include /etc/ipsec.d/*.secrets</code>
          finden. Auch sie darf nicht mit dem Zeichen <code class="computeroutput">#</code>
          beginnen.</p></li><li><p>W&auml;hlen Sie einen Namen f&uuml;r die Verbindung. Er sollte keine Sonderzeichen oder
          Leerzeichen enthalten. In diesem Beispiel wird daf&uuml;r <strong class="userinput"><code>intranator</code></strong>
          verwendet.</p></li><li><p>Legen Sie eine Datei mit dem Namen <code class="filename">/etc/ipsec.d/intranator.conf</code>
          (bzw. Ihrem Verbindungsnamen) an und &ouml;ffnen sie in einem Texteditor (z.B.
            <span class="application">nano</span> oder <span class="application">vi</span>).</p></li><li><p>Die Konfigurationsdatei beginnt mit der Zeile <strong class="userinput"><code>conn intranator</code></strong>
          (bzw. Ihrem Verbindungsnamen). Wichtig ist, dass alle folgenden Zeilen mit Leerzeichen oder
          Tabulator einger&uuml;ckt sein m&uuml;ssen. Leerzeilen sind nicht erlaubt, es muss mindestens das
          (einger&uuml;ckte) Zeichen <strong class="userinput"><code>#</code></strong> f&uuml;r einen Kommentar in einer Zeile
          enthalten sein.</p></li><li><p>Geben Sie die Daten f&uuml;r die Verbindung analog zu folgendem Beispiel ein:</p><pre class="programlisting">conn intranator
   auto=start
   keyingtries=0
   type=tunnel
   auth=esp
   authby=rsasig
   ike=aes128-sha-modp1024!
   esp=aes128-sha1!
   pfs=yes
   ikelifetime=480m
   keylife=60m
   rekey=yes
   #
   # left: our side
   left=%defaultroute
   leftid="/C=DE/S=BW/L=Tuebingen/O=Intra2net/CN=MeinRechnerName"
   leftrsasigkey=%cert
   leftcert=/etc/ipsec.d/cert.pem
   leftsubnet=192.168.10.0/24
   leftfirewall=yes       
   #
   # right: intranator side
   right=meinintranator.dyndns.org
   rightid="/CN=intranator.net.lan"
   rightrsasigkey=%cert
   rightcert=/etc/ipsec.d/intranator.pem
   rightsubnet=192.168.1.0/24
        </pre><p>Die Bedeutung der Eintr&auml;ge wird im Folgenden kurz erkl&auml;rt. Die mit
            <code class="computeroutput">left</code> beginnenden Eintr&auml;ge stehen f&uuml;r die lokale Seite,
          die mit <code class="computeroutput">right</code> beginnenden f&uuml;r die Gegenseite (hier den
          Intranator). Alle Eintr&auml;ge die nicht extra erkl&auml;rt werden, &uuml;bernehmen Sie wie
          dargestellt.</p><div class="informaltable"><table border="1"><colgroup><col><col></colgroup><tbody><tr><td>
                  <p>
                    <code class="computeroutput">auto</code>
                  </p>
                </td><td>
                  <p>Bei <strong class="userinput"><code>add</code></strong> wird die Verbindung nur geladen, bei
                      <strong class="userinput"><code>start</code></strong> automatisch aufgebaut.</p>
                </td></tr><tr><td>
                  <p>
                    <code class="computeroutput">keyingtries</code>
                  </p>
                </td><td>
                  <p>Wie oft versucht werden soll, die Verbindung aufzubauen bis wegen einem
                    Fehler abgebrochen wird. <strong class="userinput"><code>0</code></strong> steht f&uuml;r endlos.</p>
                </td></tr><tr><td>
                  <p>
                    <code class="computeroutput">ike</code>
                  </p>
                </td><td>
                  <p>Verschl&uuml;sselungsalgorithmus f&uuml;r Phase 1. Die verwendete Kombination muss im
                    Verschl&uuml;sselungsprofil des Intranators vorkommen.</p>
                </td></tr><tr><td>
                  <p>
                    <code class="computeroutput">esp</code>
                  </p>
                </td><td>
                  <p>Verschl&uuml;sselungsalgorithmus f&uuml;r Phase 2. Die verwendete Kombination muss im
                    Verschl&uuml;sselungsprofil des Intranators vorkommen.</p>
                </td></tr><tr><td>
                  <p>
                    <code class="computeroutput">pfs</code>
                  </p>
                </td><td>
                  <p>Aktiviert/Deaktiviert Perfect Forward Secrecy</p>
                </td></tr><tr><td>
                  <p>
                    <code class="computeroutput">ikelifetime</code>
                  </p>
                </td><td>
                  <p>Lebensdauer f&uuml;r Phase 1 (IKE)</p>
                </td></tr><tr><td>
                  <p>
                    <code class="computeroutput">keylife</code>
                  </p>
                </td><td>
                  <p>Lebensdauer f&uuml;r Phase 2 (IPSec)</p>
                </td></tr><tr><td>
                  <p>
                    <code class="computeroutput">left/right</code>
                  </p>
                </td><td>
                  <p>IP-Adresse oder DNS-Name. F&uuml;r die lokale Seite
                      <strong class="userinput"><code>%defaultroute</code></strong>. Wenn eine feste IP vorhanden ist, geben
                    Sie immer die IP ein und nicht einen auch noch verf&uuml;gbaren DNS-Namen.</p>
                </td></tr><tr><td>
                  <p>
                    <code class="computeroutput">leftid/rightid</code>
                  </p>
                </td><td>
                  <p>IPSec-Id der entsprechenden Seite in Anf&uuml;hrungszeichen. Geben Sie hier die
                    Inhaberdaten der Zertifikate so ein, wie Sie im Intranator in den
                    Schl&uuml;ssel-Men&uuml;s angezeigt werden.</p>
                </td></tr><tr><td>
                  <p>
                    <code class="computeroutput">leftcert/rightcert</code>
                  </p>
                </td><td>
                  <p>Dateinamen des Zertifikats der entsprechenden Seite</p>
                </td></tr><tr><td>
                  <p>
                    <code class="computeroutput">leftsubnet/rightsubnet</code>
                  </p>
                </td><td>
                  <p>Netz mit Netzmaske hinter der entsprechenden Seite. Soll auf Seite des
                    Linux-Rechners (left) nur die eine, auch extern verwendete IP per VPN verbunden
                    werden, lassen Sie den Parameter <strong class="userinput"><code>leftsubnet</code></strong> weg und
                    stellen im Intranator das <span class="guimenuitem">Netz auf Gegenseite</span> auf
                      <span class="guimenuitem">Externe IP</span>.</p>
                </td></tr><tr><td>
                  <p>
                    <code class="computeroutput">leftfirewall</code>
                  </p>
                </td><td>
                  <p>Versucht bei <strong class="userinput"><code>yes</code></strong> automatisch die lokale Firewall f&uuml;r
                    die VPN-Verbindung zu &ouml;ffnen. Dies funktioniert nur, wenn die Firewall nicht zu
                    stark angepasst wurde.</p>
                </td></tr></tbody></table></div></li><li><p>Legen Sie eine Datei mit dem Namen
            <code class="filename">/etc/ipsec.d/intranator.secrets</code> (bzw. Ihrem Verbindungsnamen) an
          und &ouml;ffnen sie in einem Texteditor (z.B. <span class="application">nano</span> oder
            <span class="application">vi</span>).</p></li><li><p>Die Datei muss auf den Dateinamen des privaten Schl&uuml;ssels verweisen:</p><pre class="programlisting">: RSA /etc/ipsec.d/private_key.pem</pre></li><li><p>In den meisten F&auml;llen m&uuml;ssen Sie dem IPSec-Dienst mitteilen, dass er neu starten soll
          um Konfigurationsdateien neu einzulesen. Dies wird normalerweise &uuml;ber den Befehl
            <strong class="userinput"><code>/etc/init.d/ipsec restart</code></strong> erreicht.</p></li><li><p>Haben Sie Ihre Verbindung auf automatisch starten gestellt, wird sie jetzt bereits im
          Hintergrund aufgebaut. Wenn Sie sie manuell starten m&ouml;chten, k&ouml;nnen Sie dies mit
            <strong class="userinput"><code>ipsec auto --up intranator</code></strong> (bzw. Ihrem Verbindungsnamen)
          tun.</p><p>Protokolle des Verbindungsaufbaus finden Sie mit der Dienstkennung
            <code class="computeroutput">pluto</code> in einer der Logdateien des Systems, bei
          aktuellen Distributionen meistens <code class="filename">/var/log/secure</code>.</p></li></ol></div><a class="indexterm" name="d0e16103"></a><a class="indexterm" name="d0e16104"></a><a class="indexterm" name="d0e16105"></a></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="vpn-linux-xswan-cert.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="vpn-linux-xswan.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="vpn-linux-xswan-intranator.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">53.2. Zertifikate erzeugen&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;53.4. Intranator</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>