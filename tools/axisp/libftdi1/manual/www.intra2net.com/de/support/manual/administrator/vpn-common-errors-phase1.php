<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Fehler in Phase 1 | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="vpn-common-errors.php" title="55. Kapitel - Fehlerdiagnose"><link rel="prev" href="vpn-common-errors-logformat.php" title="55.2. Das Protokollformat des Intranators"><link rel="next" href="vpn-common-errors-phase2.php" title="55.4. Fehler in Phase 2">
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

<a href="vpn-common-errors-phase1.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="vpn-common-errors-phase1.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">55.3. Fehler in Phase 1</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="vpn-common-errors-logformat.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">55. Kapitel - Fehlerdiagnose</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="vpn-common-errors-phase2.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="vpn-common-errors-phase1"></a>55.3. Fehler in Phase 1</h2></div></div></div><p>Fehler in Phase 1 bedeuten meistens eine falsche Konfiguration der Authentifizierung (z.B.
      falsche Zertifikate konfiguriert oder eine andere IPSec-ID verwendet) oder in seltenen F&auml;llen
      auch falsch konfigurierte Verschl&uuml;sselungsalgorithmen.</p><p>Am Anfang jeder Verbindung tauschen die Gegenstellen typischerweise Informationen &uuml;ber
      ihre F&auml;higkeiten aus und erkennen, ob die Verbindung durch NAT l&auml;uft:
      </p><pre class="programlisting">packet from 192.168.1.200:500: received Vendor ID payload [draft-ietf-
    ipsec-nat-t-ike-00]
packet from 192.168.1.200:500: received Vendor ID payload [draft-ietf-
    ipsec-nat-t-ike-02_n]
responding to Main Mode from unknown peer 192.168.1.200
ignoring Vendor ID payload [47bbe7c993f1fc13b4e6d0db565c68e50102010...]
ignoring Vendor ID payload [da8e937880010000]
received Vendor ID payload [Dead Peer Detection]
received Vendor ID payload [XAUTH]
NAT-Traversal: Result using draft-ietf-ipsec-nat-t-ike-02/03: no NAT detected
ignoring informational payload, type IPSEC_REPLAY_STATUS
ignoring informational payload, type IPSEC_INITIAL_CONTACT</pre><p>Danach sendet derjenige, der die Verbindung initiiert, sein Zertifikat:
      </p><pre class="programlisting">Peer ID is ID_DER_ASN1_DN: 'CN=client1'</pre><p>Das System &uuml;berpr&uuml;ft, ob das Zertifikat &uuml;ber Zertifizierungsstellen vertrauensw&uuml;rdig ist.
      Da der Intranator diese Funktion nicht verwendet, schl&auml;gt das immer fehl:
      </p><pre class="programlisting">issuer cacert not found
X.509 certificate rejected</pre><p>Als n&auml;chstes wird gepr&uuml;ft, ob das Zertifikat bekannt ist. In diesem Beispiel schl&auml;gt das
      fehl, da ein anderes Zertifikat konfiguriert ist:
      </p><pre class="programlisting">no RSA public key known for 'CN=client1'</pre><p>Der Intranator sendet daher eine kurze Fehlerinformation an die Gegenstelle:
      </p><pre class="programlisting">sending encrypted notification INVALID_KEY_INFORMATION to 192.168.1.200:500</pre><p>Baut der Intranator hingegen von sich aus die Verbindung auf, bekommen wir bei dem selben
      Fehler nur wesentlich weniger Informationen:
      </p><pre class="programlisting">we have a cert and are sending it
ignoring informational payload, type INVALID_CERTIFICATE</pre><p>In diesem Fall sollte das Log der Gegenstelle genauer untersucht werden, hier sind dann
      meistens detailliertere Informationen zu finden.</p><p>M&ouml;chte die Gegenstelle die Verbindung mit einem nicht erlaubten
      Verschl&uuml;sselungsalgorithmus aufbauen (in diesem Beispiel einfaches DES), wird folgendes
      Protokolliert:
      </p><pre class="programlisting">OAKLEY_DES_CBC is not supported.  Attribute OAKLEY_ENCRYPTION_ALGORITHM</pre><p>Die Gegenstelle kann mehrere Algorithmen vorschlagen. Ist kein akzeptabler dabei,
      protokolliert der Intranator dies und sendet der Gegenstelle eine entsprechende Meldung:
      </p><pre class="programlisting">no acceptable Oakley Transform
sending notification NO_PROPOSAL_CHOSEN to 192.168.1.200:500</pre><p>In diesem Fall muss das Verschl&uuml;sselungsprofil auf dem Intranator oder der Gegenseite so
      angepasst werden, dass mindestens eine Algorithmenkombination auf beiden Seiten zul&auml;ssig ist.</p><p>Ist dagegen alles korrekt konfiguriert, wird die Phase 1 erfolgreich abgeschlossen:
      </p><pre class="programlisting">sent MR3, ISAKMP SA established</pre></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="vpn-common-errors-logformat.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="vpn-common-errors.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="vpn-common-errors-phase2.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">55.2. Das Protokollformat des Intranators&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;55.4. Fehler in Phase 2</td></tr></table></div>
      
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